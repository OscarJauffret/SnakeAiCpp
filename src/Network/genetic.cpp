//
// Created by oscar on 14/07/2024.
//

#include <format>
#include "headers/genetic.hpp"

Genetic::Genetic(Renderer &renderer): window(renderer.getWindow()), renderer(renderer),
pool(config::genetic::numThreads), timePerFrame(Renderer::getTimePerFrame()) {
    initializePopulation(config::genetic::populationSize,
                         config::net::inputSize,
                         config::net::outputSize);
    renderer.setNetworkGenome(population[0]);
}

void Genetic::initializePopulation(int populationSize, int inputSize, int outputSize) {
    for (int i = 0; i < populationSize; i++) {
        population.emplace_back(inputSize, outputSize);
    }
}

void Genetic::train() {
    auto start = high_resolution_clock::now();
    render(false);
    while (window.isOpen() && !stop) {
        population = selection();
        fitnesses.push_back(population[0].getFitness());
        renderer.setNetworkGenome(population[0]);
        generations++;
        cout << "Generation: " << generations << " Best fitness: " << format("{:.2f}", fitnesses.back()) << endl;
        computePopulationStats();
        auto now = chrono::high_resolution_clock::now();
        realTrainingTime = duration_cast<chrono::seconds>(now - start).count();

        render(false);
        if (showBest) {
            replayBestGenome();
            render(false);
        }

        vector<Genome> newPopulation = initializeNewPopulationWithElites();
        while (newPopulation.size() < config::genetic::populationSize) {
            newPopulation.push_back(population[tournamentSelection()]);
            Mutator::mutate(newPopulation.back());
        }
        population = newPopulation;
    }
}

vector<Genome> Genetic::initializeNewPopulationWithElites() {
     vector<Genome> newPopulation;

    int eliteCount = config::genetic::populationSize * config::genetic::elitismRate;
    newPopulation.reserve(eliteCount);
    std::copy(population.begin(), population.begin() + eliteCount, std::back_inserter(newPopulation));

    return newPopulation;
}

float Genetic::calculateTotalFitness() {
    float totalFitness = 0;
    for (const Genome& genome: population) {
        totalFitness += genome.getFitness();
    }
    return totalFitness;
}

int Genetic::tournamentSelection() {
    const int tournamentSize = 3;
    vector<int> tournamentParticipants;

    for (int i = 0; i < tournamentSize; ++i) {
        int randomIndex = selectRandomGenomeBasedOnFitness();
        tournamentParticipants.push_back(randomIndex);
    }

    int bestParticipant = tournamentParticipants[0];
    float bestFitness = population[tournamentParticipants[0]].getFitness();
    for (int i = 1; i < tournamentParticipants.size(); ++i) {
        int participantIndex = tournamentParticipants[i];
        float participantFitness = population[participantIndex].getFitness();
        if (participantFitness > bestFitness) {
            bestParticipant = participantIndex;
            bestFitness = participantFitness;
        }
    }
    return bestParticipant;
}

int Genetic::selectRandomGenomeBasedOnFitness() {
    float totalFitness = calculateTotalFitness();
    if (totalFitness == 0) {
        return 0;
    }
    float randomFitness = RNG::randomFloatBetween(0, totalFitness);
    float currentFitness = 0;
    int i = 0;
    for (const Genome& genome: population) {
        currentFitness += genome.getFitness();
        if (randomFitness <= currentFitness) {
            return i;
        }
        i++;
    }
    return 0;
}

vector<Genome> Genetic::trainAgents(vector<Genome> pop) {
    vector<std::future<void>> futures;

    for (Genome &genome: pop) {
        futures.push_back(pool.enqueue([&genome, this]() mutable {
            StatsTracker statsTracker;
            trainAgent(genome, false, renderer.getSnakeRenderer(),
                       config::genetic::numberOfGamesPerAgent, config::game::accelerationFactor, statsTracker);
            genome.setFitness(statsTracker.fitness);
            genome.setGameOvers(statsTracker.deathReasons);
            genome.setTrainingTime(statsTracker.trainingTime);
        }));
    }

    while (!futures.empty()) {
        // Traiter les événements de la fenêtre ici
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return {};
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    showBest = !showBest;
                    cout << "Show best: " << showBest << endl;
                    render(false);
                }
            }
        }
        futures.erase(remove_if(futures.begin(), futures.end(),
                                [](const future<void> &fut) { return fut.wait_for(chrono::seconds(0)) == future_status::ready; }),
                      futures.end());
    }

    return pop;
}

void
Genetic::trainAgent(Genome genome, bool shouldRender, SnakeRenderer &snakeRenderer, int numberOfGames,
                    float accelerationFactor, StatsTracker &statsTracker) {
    Engine engine(window, timePerFrame, Mode::Ai, genome, snakeRenderer, shouldRender, numberOfGames, statsTracker);
    engine.run(accelerationFactor);
}


vector<Genome> Genetic::selection() {
    vector<Genome> newPopulation = trainAgents(population);
    std::sort(newPopulation.begin(), newPopulation.end(), [](Genome& a, Genome& b) -> bool {
        return a.getFitness() > b.getFitness();
    });
    return newPopulation;
}

void Genetic::render(bool isControlled) {
    TrainingInfo trainingInfo(generations, realTrainingTime, virtualTrainingTime, showBest);
    renderer.render(deathReasonsCount, trainingInfo);
}

void Genetic::replayBestGenome() {
    promise<void> prom;
    future<void> fut = prom.get_future();
    thread([prom = std::move(prom), this]() mutable {
        StatsTracker statsTracker;
        trainAgent(population[0], true, renderer.getSnakeRenderer(), 1, 1, statsTracker);
        prom.set_value();
    }).detach();

    while (fut.wait_for(chrono::seconds(0)) != future_status::ready){
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    showBest = !showBest;
                } else if (event.key.code == sf::Keyboard::Backspace) {
                    stop = true;
                }
            }
        }
        render(true);
    }
}

void Genetic::computePopulationStats() {
    deathReasonsCount.push_back({0, 0, 0, 0});
    for (const Genome& genome: population) {
        for (const auto& reason: genome.getGameOvers()) {
            deathReasonsCount.back()[(int) reason]++;
        }
        virtualTrainingTime += genome.getTrainingTime();
    }
}

