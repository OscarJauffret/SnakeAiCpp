//
// Created by oscar on 15/07/2024.
//

#ifndef SNAKEAI_SNAKEPART_HPP
#define SNAKEAI_SNAKEPART_HPP
#include <SFML/Graphics.hpp>

using namespace sf;

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct SnakePart {
    Vector2i position;
};

enum class GameOverType {
    Starvation = 0,
    Suicide = 1,
    Collision = 2,
    Won = 3
};

#endif //SNAKEAI_SNAKEPART_HPP
