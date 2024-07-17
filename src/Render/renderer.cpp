//
// Created by oscar on 13/07/2024.
//

#include "headers/renderer.hpp"

const Time Renderer::timePerFrame = seconds(1.f / config::window::fps);

Renderer::Renderer(SnakeRenderer &snakeRenderer, NetworkRenderer &networkRenderer, StatsRenderer &statsRenderer,
                   TrainingRenderer &trainingRenderer)
: snakeRenderer(snakeRenderer), networkRenderer(networkRenderer), statsRenderer(statsRenderer), trainingRenderer(trainingRenderer),
    resolution(config::window::width, config::window::height),
    window(VideoMode(resolution.x, resolution.y), config::window::title,
    config::window::style, ContextSettings(0, 0, 8)) {
    window.setFramerateLimit(config::window::fps);
    if (!font.loadFromFile(config::assets::fontPath)) {
        cerr << "Failed to load font" << endl;
    }
}

void Renderer::render(const vector<vector<int>> &deathReasonsCount, TrainingInfo &trainingInfo) {
    window.clear(config::colors::bgColor);
    snakeRenderer.render(window);
    networkRenderer.render(window);
    statsRenderer.render(window, font, deathReasonsCount);
    trainingRenderer.render(window, font, trainingInfo);
    window.display();
}

RenderWindow &Renderer::getWindow() {
    return window;
}

Time Renderer::getTimePerFrame() {
    return timePerFrame;
}

void Renderer::setNetworkGenome(Genome &genome) {
    networkRenderer.setGenome(genome);
}

SnakeRenderer &Renderer::getSnakeRenderer() {
    return snakeRenderer;
}

Mode Renderer::askMode() {
    Button manualButton = createModeButton(true);
    Button aiButton = createModeButton(false);
    Mode mode = Mode::Manual;
    bool chosen = false;
    while (window.isOpen() && !chosen) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (manualButton.isMouseOver(window)) {
                        mode = Mode::Manual;
                        chosen = true;
                    } else if (aiButton.isMouseOver(window)) {
                        mode = Mode::Ai;
                        chosen = true;
                    }
                }
            }
        }

        window.clear(config::colors::bgColor);
        manualButton.draw(window);
        aiButton.draw(window);
        window.display();
    }
    return mode;
}

Button Renderer::createModeButton(bool isManualButton) {
    float buttonHeight = 200;
    float buttonWidth = buttonHeight * M_PHI;
    float buttonX = resolution.x / 2 - 5;
    if (isManualButton) {
        buttonX -= buttonWidth + 10;
    }
    float buttonY = resolution.y / 2 - buttonHeight / 2;
    string text = isManualButton ? "Manual" : "AI";

    return {buttonX, buttonY, buttonWidth, buttonHeight, text, font};
}
