//
// Created by oscar on 13/07/2024.
//

#include "headers/engine.hpp"

Engine::Engine(RenderWindow &window, Time timePerFrame, Mode mode, Genome genome, SnakeRenderer &snakeRenderer,
               bool shouldRender, int numberOfGames, StatsTracker &statsTracker)
: window(window), timePerFrame(timePerFrame), framesElapsed(0), numberOfGamesMax(numberOfGames), shouldRender(shouldRender), snakeRenderer(snakeRenderer),
  snake({config::game::snakeStartPos}, Direction::RIGHT, config::game::startLength, shouldRender, snakeRenderer),
  mode(mode), controllingAgent(std::move(genome)), statsTracker(statsTracker) {

}

void Engine::run(float accelerationFactor) {
    auto start = high_resolution_clock::now();
    clock.restart();
    timeSinceLastUpdate = Time::Zero;
    spawnFood();
    renderSnakeIfManualMode();

    while (window.isOpen() && numberOfGamesPlayed < numberOfGamesMax && numberOfMovesWithoutFood < config::game::maxMovesWithoutFood) {
        Time dt = clock.restart();  // Restart the clock and return the time elapsed since the last restart
        dt *= accelerationFactor;
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > timePerFrame) {
            if (numberOfGamesPlayed >= numberOfGamesMax) {
                break;
            }
            timeSinceLastUpdate -= timePerFrame;

            input();
            checkFood();
            snake.update();
            framesElapsed++;
            numberOfMovesWithoutFood++;
            if (snake.dies(deathType) || starves(deathType)) {
                restartGame();
                statsTracker.deathReasons.push_back(deathType);
            }
            snake.updateRender(foodPos);
            renderSnakeIfManualMode();
        }
    }
    statsTracker.fitness /= (float) numberOfGamesMax;
    auto stop = high_resolution_clock::now();
    statsTracker.trainingTime = duration_cast<chrono::milliseconds>(stop - start).count() * (duration_t) accelerationFactor / 1000;
}

bool Engine::starves(GameOverType &reason) const {
    if (numberOfMovesWithoutFood >= config::game::maxMovesWithoutFood * snake.getLength()) {
        reason = GameOverType::Starvation;
        return true;
    }
    return false;
}

void Engine::checkFood() {
    if (snake.isCollidingWithSnake(foodPos)) {
        snake.grow();
        spawnFood();
        numberOfMovesWithoutFood = 0;
    }
}

void Engine::renderSnakeIfManualMode() {
    if (mode == Mode::Manual) {
        snake.askToRender(window);
    }
}

void Engine::restartGame() {
    numberOfGamesPlayed++;
    statsTracker.fitness += (float) snake.getLength();
    framesElapsed = 0;
    numberOfMovesWithoutFood = 0;
    snake = std::move(Snake({config::game::snakeStartPos}, Direction::RIGHT, config::game::startLength, shouldRender, snakeRenderer));
    spawnFood();
}

void Engine::spawnFood() {
    do {
        foodPos = Vector2i(RNG::randomIntBetween(0, config::game::gridSize.x - 1), RNG::randomIntBetween(0, config::game::gridSize.y - 1));
    } while (snake.isCollidingWithSnake(foodPos));
}

float Engine::getInputValue(int inputId) {
    Direction snakeDirection = snake.getDirection();
    Vector2i headPos = snake.getHeadPosition();
    Vector2i pointUp = headPos + Vector2i(0, -1);
    Vector2i pointDown = headPos + Vector2i(0, 1);
    Vector2i pointLeft = headPos + Vector2i(-1, 0);
    Vector2i pointRight = headPos + Vector2i(1, 0);
    switch (inputId) {
        case 0:
            return snakeDirection == Direction::UP ? 1 : 0;
        case 1:
            return snakeDirection == Direction::DOWN ? 1 : 0;
        case 2:
            return snakeDirection == Direction::LEFT ? 1 : 0;
        case 3:
            return snakeDirection == Direction::RIGHT ? 1 : 0;
        case 4:
            return foodPos.x < headPos.x ? 1 : 0;
        case 5:
            return foodPos.x > headPos.x ? 1 : 0;
        case 6:
            return foodPos.y < headPos.y ? 1 : 0;
        case 7:
            return foodPos.y > headPos.y ? 1 : 0;
        case 8: {
            bool dangerAhead = (snakeDirection == Direction::UP && snake.isDangerous(pointUp) ? 1 : 0)
                               || (snakeDirection == Direction::DOWN && snake.isDangerous(pointDown) ? 1 : 0)
                               || (snakeDirection == Direction::LEFT && snake.isDangerous(pointLeft) ? 1 : 0)
                               || (snakeDirection == Direction::RIGHT && snake.isDangerous(pointRight) ? 1 : 0);
            return dangerAhead;
        }
        case 9: {
            bool dangerLeft = (snakeDirection == Direction::UP && snake.isDangerous(pointLeft) ? 1 : 0)
                              || (snakeDirection == Direction::DOWN && snake.isDangerous(pointRight) ? 1 : 0)
                              || (snakeDirection == Direction::LEFT && snake.isDangerous(pointDown) ? 1 : 0)
                              || (snakeDirection == Direction::RIGHT && snake.isDangerous(pointUp) ? 1 : 0);
            return dangerLeft;
        }
        case 10: {
            bool dangerRight = (snakeDirection == Direction::UP && snake.isDangerous(pointRight) ? 1 : 0)
                               || (snakeDirection == Direction::DOWN && snake.isDangerous(pointLeft) ? 1 : 0)
                               || (snakeDirection == Direction::LEFT && snake.isDangerous(pointUp) ? 1 : 0)
                               || (snakeDirection == Direction::RIGHT && snake.isDangerous(pointDown) ? 1 : 0);
            return dangerRight;
        }
        default:
            return 0;
    }
}