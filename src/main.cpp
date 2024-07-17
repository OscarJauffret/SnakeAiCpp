#include <iostream>
#include "Render/headers/renderer.hpp"
#include "Render/headers/snakerenderer.hpp"
#include "Engine/headers/engine.hpp"
#include "Network/headers/genetic.hpp"

void launchGame(Renderer &renderer);

SnakeRenderer snakeRenderer;
NetworkRenderer networkRenderer;
StatsRenderer statsRenderer;
TrainingRenderer trainingRenderer;

int main() {
    Renderer renderer(snakeRenderer, networkRenderer, statsRenderer, trainingRenderer);
    launchGame(renderer);
    return 0;
}

void launchGame(Renderer &renderer) {
    Mode mode = renderer.askMode();
    if (mode == Mode::Manual) {
        StatsTracker statsTracker;
        Engine engine(renderer.getWindow(), Renderer::getTimePerFrame(), Mode::Manual, Genome(0, 0),
                      snakeRenderer, true, 100, statsTracker);
        engine.run(1);
    } else {
        Genetic genetic(renderer);
        genetic.train();
    }
}
