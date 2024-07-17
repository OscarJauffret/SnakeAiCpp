//
// Created by oscar on 17/07/2024.
//

#include "headers/trainingrenderer.hpp"

void TrainingRenderer::render(RenderWindow &window, Font &font, TrainingInfo &trainingInfo) {
    drawBackground(window);
    drawGeneration(window, font, trainingInfo.generations);
    drawRealTime(window, font, trainingInfo.realTrainingTime);
    drawVirtualTime(window, font, trainingInfo.virtualTrainingTime);
}

void TrainingRenderer::drawBackground(RenderWindow &window) {
    RectangleShape bg = Card::make(Vector2i(config::layout::traininginfo::originX, config::layout::traininginfo::originY),
                                    Vector2i(config::layout::traininginfo::width, config::layout::traininginfo::height),
                                    config::colors::darkerBgColor, 2, config::colors::traininginfo::outlineColor);
    window.draw(bg);
}

void TrainingRenderer::drawGeneration(RenderWindow &window, Font &font, int generation) {
    Text text = TextUtils::make("Generation: " + std::to_string(generation), config::layout::traininginfo::generationTextSize,
                                config::colors::textColor,
                                Vector2f(config::layout::traininginfo::originX + 5.0f, config::layout::traininginfo::originY + 5.0f),
                                font);
    window.draw(text);
}

void TrainingRenderer::drawRealTime(RenderWindow &window, Font &font, duration_t realTime) {
    Text text = TextUtils::make("Real training time:\n" + TextUtils::formatTime(realTime), config::layout::traininginfo::timeTextSize,
                                config::colors::textColor,Vector2f(config::layout::traininginfo::originX + 5.0f, config::layout::traininginfo::originY + 30.0f),
                                font);
    window.draw(text);
}

void TrainingRenderer::drawVirtualTime(RenderWindow &window, Font &font, duration_t virtualTime) {
    Text text = TextUtils::make("Simulated training time:\n" + TextUtils::formatTime(virtualTime), config::layout::traininginfo::timeTextSize,
                                config::colors::textColor, Vector2f(config::layout::traininginfo::originX + 5.0f, config::layout::traininginfo::originY + 60.0f),
                                font);
    window.draw(text);

}
