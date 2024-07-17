//
// Created by oscar on 13/07/2024.
//

#ifndef SNAKEAI_SNAKE_HPP
#define SNAKEAI_SNAKE_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include "snakepart.hpp"
#include "../../Render/headers/snakerenderer.hpp"
using namespace sf;
using namespace std;



class Snake {
    SnakePart head;
    vector<SnakePart> body;
    Direction direction;
    Direction clockWiseDirections[4] = {Direction::RIGHT, Direction::DOWN, Direction::LEFT, Direction::UP};
    int length;

    bool render;
    SnakeRenderer& renderer;
public:
    Snake(Vector2i position, Direction direction, int length, bool render, SnakeRenderer &renderer);
    void update();
    void updateRender(Vector2i foodPos);
    void askToRender(RenderWindow &window);
    void grow();

    static Vector2i directionToVector(Direction direction);
    void changeDirection(Direction newDirection);
    static bool areDirectionsOpposite(Direction direction1, Direction direction2);
    void setNewDirection(int input);

    [[nodiscard]] Vector2i getHeadPosition() const;
    [[nodiscard]] int getLength() const;
    [[nodiscard]] Direction getDirection();
    bool isCollidingWithSnake(Vector2i position);

    bool isDangerous(Vector2i position);
    [[nodiscard]] bool isCollidingWithWall() const;
    bool isCollidingWithItself();
    bool dies(GameOverType &reason);

    Snake(const Snake&) = delete;
    Snake& operator=(const Snake&) = delete;

    // Define move constructor
    Snake(Snake&& other) noexcept
        : head(std::move(other.head)), direction(other.direction), length(other.length), render(other.render), renderer(other.renderer), body(std::move(other.body)) {
        other.length = 0;
    }

    // Define move assignment operator
    Snake& operator=(Snake&& other) noexcept {
        if (this != &other) {
            head = std::move(other.head);
            direction = other.direction;
            length = other.length;
            render = other.render;
            renderer = other.renderer;
            body = std::move(other.body);
            other.length = 0;
        }
        return *this;
    }
};


#endif //SNAKEAI_SNAKE_HPP
