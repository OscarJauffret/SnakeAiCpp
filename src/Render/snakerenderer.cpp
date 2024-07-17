//
// Created by oscar on 15/07/2024.
//

#include <utility>
#include "headers/snakerenderer.hpp"

SnakeRenderer::SnakeRenderer() {
    foodPos = {0, 0};

}

void SnakeRenderer::update(SnakePart head, vector<SnakePart> snk, Vector2i foodPos) {
    this->head = head;
    this->snake = std::move(snk);
    this->foodPos = foodPos;
}

void SnakeRenderer::render(sf::RenderWindow &window) {
    Vector2i origin = {config::layout::snake::originX, config::layout::snake::originY};
    RectangleShape background = Card::make(origin, {config::layout::snake::width, config::layout::snake::height},
                                 config::colors::darkerBgColor, 2, Color::White);
    window.draw(background);
    RectangleShape headRectangle(Vector2f(config::game::cellSize, config::game::cellSize));
    headRectangle.setPosition(Vector2f(origin.x + this->head.position.x * config::game::cellSize,
                                       origin.y + this->head.position.y * config::game::cellSize));
    headRectangle.setFillColor(config::colors::snakeColor);
    window.draw(headRectangle);

    for (auto &part : this->snake) {
        RectangleShape rectangle(Vector2f(config::game::cellSize, config::game::cellSize));
        rectangle.setPosition(Vector2f(origin.x + part.position.x * config::game::cellSize,
                                       origin.y + part.position.y * config::game::cellSize));
        rectangle.setFillColor(config::colors::snakeColor);
        window.draw(rectangle);
    }

    RectangleShape foodRectangle(Vector2f(config::game::cellSize, config::game::cellSize));
    foodRectangle.setPosition(Vector2f(origin.x +foodPos.x * config::game::cellSize,
                                       origin.y +foodPos.y * config::game::cellSize));
    foodRectangle.setFillColor(config::colors::foodColor);
    window.draw(foodRectangle);
}