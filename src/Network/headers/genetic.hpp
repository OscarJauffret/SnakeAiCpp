//
// Created by oscar on 14/07/2024.
//

#ifndef MINESWEEPERAI_GENETIC_HPP
#define MINESWEEPERAI_GENETIC_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <algorithm>
#include <chrono>
#include "genome.hpp"
#include "../../Render/headers/renderer.hpp"
#include "../../config.hpp"
#include "threadpool.hpp"
#include "mutator.hpp"
#include "../../Engine/headers/engine.hpp"


using namespace std;
using namespace std::chrono;
using namespace sf;

class Genetic {
    int generations = 0;
    vector<float> fitnesses;
    duration_t realTrainingTime = 0;
    duration_t virtualTrainingTime = 0;
    vector<vector<int>> deathReasonsCount = {};

    vector<Genome> population;
    RenderWindow& window;
    Renderer& renderer;
    Time timePerFrame;

    ThreadPool pool;

    bool stop = false;
    bool showBest = false;
public:
    explicit Genetic(Renderer &renderer);
    void train();
    vector<Genome> trainAgents(vector<Genome> pop);
    void trainAgent(Genome genome, bool shouldRender, SnakeRenderer &snakeRenderer, int numberOfGames,
                    float accelerationFactor, StatsTracker &statsTracker);

    void initializePopulation(int populationSize, int inputSize, int outputSize);
    vector<Genome> selection();
    vector<Genome> initializeNewPopulationWithElites();
    float calculateTotalFitness();
    int tournamentSelection();
    int selectRandomGenomeBasedOnFitness();

    void render(bool isControlled);
    void replayBestGenome();

    void computePopulationStats();

};


#endif //MINESWEEPERAI_GENETIC_HPP
