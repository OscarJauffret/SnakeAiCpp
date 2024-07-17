//
// Created by oscar on 15/07/2024.
//

#ifndef SNAKEAI_SNAKERENDERER_HPP
#define SNAKEAI_SNAKERENDERER_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "../../Engine/headers/snakepart.hpp"
#include "../../config.hpp"
#include "card.hpp"

using namespace sf;
using namespace std;

class SnakeRenderer {
    SnakePart head;
    vector<SnakePart> snake;
    Vector2i foodPos;
public:
    SnakeRenderer();
    void update(SnakePart head, vector<SnakePart> snk, Vector2i foodPos);
    void render(RenderWindow &window);
};


#endif //SNAKEAI_SNAKERENDERER_HPP
