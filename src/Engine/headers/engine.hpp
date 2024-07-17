//
// Created by oscar on 13/07/2024.
//

#ifndef SNAKEAI_ENGINE_HPP
#define SNAKEAI_ENGINE_HPP
#include "../../config.hpp"
#include "snake.hpp"
#include "rng.hpp"
#include "../../Network/headers/genome.hpp"
#include "statstracker.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>

using namespace std::chrono;

class Engine {
    RenderWindow &window;
    Time timePerFrame;

    Vector2i foodPos;

    int numberOfGamesMax = 0;
    int numberOfGamesPlayed = 0;
    int numberOfMovesWithoutFood = 0;
    Genome controllingAgent;
    Mode mode;

    Clock clock;
    Time timeSinceLastUpdate;
    SnakeRenderer &snakeRenderer;

    Snake snake;
    uint64_t framesElapsed = 0;
    bool shouldRender;

    GameOverType deathType = GameOverType::Starvation;

    StatsTracker &statsTracker;
public:
    Engine(RenderWindow &window, Time timePerFrame, Mode mode, Genome genome, SnakeRenderer &snakeRenderer,
           bool shouldRender, int numberOfGames, StatsTracker &statsTracker);
    void run(float accelerationFactor);

    int input();
    int userInput();
    int AiInput();

    void spawnFood();
    void restartGame();
    void checkFood();

    void renderSnakeIfManualMode();

    float getInputValue(int inputId);

    bool starves(GameOverType &reason) const;
};


#endif //SNAKEAI_ENGINE_HPP
