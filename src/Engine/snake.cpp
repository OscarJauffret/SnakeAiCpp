//
// Created by oscar on 13/07/2024.
//

#include "headers/snake.hpp"

Snake::Snake(Vector2i position, Direction direction, int length, bool render, SnakeRenderer &renderer)
        : head({position}), direction(direction), length(length), render(render), renderer(renderer) {
    for (int i = 0; i < length; i++) {
        body.push_back({position});
    }
}

void Snake::update() {
    for (int i = length - 1; i > 0; i--) {
        body[i].position = body[i - 1].position;
    }
    head.position += directionToVector(direction);
    body[0].position = head.position;
}

void Snake::grow() {
    body.push_back({body.back().position});
    length++;
}

Vector2i Snake::directionToVector(Direction direction) {
    switch (direction) {
        case Direction::UP:
            return {0, -1};
        case Direction::DOWN:
            return {0, 1};
        case Direction::LEFT:
            return {-1, 0};
        case Direction::RIGHT:
            return {1, 0};
    }
    return {0, 0};
}

void Snake::changeDirection(Direction newDirection) {
    if (areDirectionsOpposite(direction, newDirection)) {
        return;
    }
    direction = newDirection;
}

Vector2i Snake::getHeadPosition() const {
    return head.position;
}

int Snake::getLength() const {
    return length;
}

bool Snake::areDirectionsOpposite(Direction direction1, Direction direction2) {
    if (direction1 == Direction::UP && direction2 == Direction::DOWN) {
        return true;
    }
    if (direction1 == Direction::DOWN && direction2 == Direction::UP) {
        return true;
    }
    if (direction1 == Direction::LEFT && direction2 == Direction::RIGHT) {
        return true;
    }
    if (direction1 == Direction::RIGHT && direction2 == Direction::LEFT) {
        return true;
    }
    return false;
}

void Snake::setNewDirection(int input) {
    int index = 0;
    for (int i = 0; i < 4; i++) {
        if (direction == clockWiseDirections[i]) {
            index = i;
            break;
        }
    }
    if (input == 1) {   // turn right
        int nextIndex = (index + 1) % 4;
        direction = clockWiseDirections[nextIndex];
    }
    if (input == 2) {   // turn left
        int nextIndex = (index + 3) % 4;
        direction = clockWiseDirections[nextIndex];
    }
}

void Snake::updateRender(Vector2i foodPos) {
    if (render) {
        renderer.update(head, body, foodPos);
    }
}

void Snake::askToRender(RenderWindow &window) {
    window.clear(config::colors::bgColor);
    renderer.render(window);
    window.display();
}

bool Snake::isCollidingWithSnake(Vector2i position) {
    if (head.position == position) {
        return true;
    }
    for (auto &part : body) {
        if (part.position == position) {
            return true;
        }
    }
    return false;
}

bool Snake::isCollidingWithWall() const {
    return head.position.x < 0 || head.position.x >= config::game::gridSize.x ||
           head.position.y < 0 || head.position.y >= config::game::gridSize.y;
}

bool Snake::isCollidingWithItself() {
    for (int i = 1; i < length; i++) {
        if (head.position == body[i].position) {
            return true;
        }
    }
    return false;
}

bool Snake::dies(GameOverType &reason) {
    if (isCollidingWithWall()) {
        reason = GameOverType::Collision;
        return true;
    } else if (isCollidingWithItself()) {
        reason = GameOverType::Suicide;
        return true;
    }
    return false;
}

Direction Snake::getDirection() {
    return direction;
}

bool Snake::isDangerous(Vector2i position) {
    if (position.x < 0 || position.x >= config::game::gridSize.x || position.y < 0 || position.y >= config::game::gridSize.y) {     // check if the position is out of bounds
        return true;
    }
    if (isCollidingWithSnake(position)) {       // check if the position is colliding with the snake
        return true;
    }
    return false;
}
