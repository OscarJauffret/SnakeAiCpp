//
// Created by oscar on 17/07/2024.
//

#ifndef SNAKEAI_TRAININGRENDERER_HPP
#define SNAKEAI_TRAININGRENDERER_HPP

#include <SFML/Graphics.hpp>
#include "../../config.hpp"
#include "traininginfo.hpp"
#include "card.hpp"
#include "textutils.hpp"

using namespace sf;

class TrainingRenderer {
public:
    static void render(RenderWindow &window, Font &font, TrainingInfo &trainingInfo);
    static void drawBackground(RenderWindow &window);
    static void drawGeneration(RenderWindow &window, Font &font, int generation);
    static void drawRealTime(RenderWindow &window, Font &font, duration_t realTime);
    static void drawVirtualTime(RenderWindow &window, Font &font, duration_t virtualTime);
};


#endif //SNAKEAI_TRAININGRENDERER_HPP
