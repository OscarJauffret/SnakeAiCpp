//
// Created by oscar on 13/07/2024.
//
#include "headers/engine.hpp"

int Engine::input() {
    if (mode == Mode::Manual) {
        return userInput();
    } else {
        return AiInput();
    }
}

int Engine::userInput() {
    Event event{};
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::KeyPressed) {
            switch (event.key.code) {
                case Keyboard::Up:
                    snake.changeDirection(Direction::UP);
                    break;
                case Keyboard::Down:
                    snake.changeDirection(Direction::DOWN);
                    break;
                case Keyboard::Left:
                    snake.changeDirection(Direction::LEFT);
                    break;
                case Keyboard::Right:
                    snake.changeDirection(Direction::RIGHT);
                    break;
                case Keyboard::Escape:
                    window.close();
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

int Engine::AiInput() {
    vector<float> inputs = {};
    for (int i = 0; i < config::net::inputSize; i++) {
        inputs.push_back(getInputValue(i));
    }
    int moveIndex = controllingAgent.predict(inputs);
    // say 0 is straight, 1 is right, 2 is left
    snake.setNewDirection(moveIndex);
    return moveIndex;
}


