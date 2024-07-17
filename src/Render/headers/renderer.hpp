//
// Created by oscar on 13/07/2024.
//

#ifndef SNAKEAI_RENDERER_HPP
#define SNAKEAI_RENDERER_HPP

#include "../../config.hpp"
#include "snakerenderer.hpp"
#include "networkrenderer.hpp"
#include "statsrenderer.hpp"
#include "trainingrenderer.hpp"
#include "button.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Renderer {
    Vector2i resolution;
    const unsigned int FPS = config::window::fps;
    static const Time timePerFrame;
    Font font;

    RenderWindow window;
    SnakeRenderer &snakeRenderer;
    NetworkRenderer &networkRenderer;
    StatsRenderer &statsRenderer;
    TrainingRenderer &trainingRenderer;
public:
    explicit Renderer(SnakeRenderer &snakeRenderer, NetworkRenderer &networkRenderer, StatsRenderer &statsRenderer,
                      TrainingRenderer &trainingRenderer);
    Mode askMode();
    Button createModeButton(bool isManualButton);

    void render(const vector<vector<int>> &deathReasonsCount, TrainingInfo &trainingInfo);

    RenderWindow &getWindow();
    static Time getTimePerFrame();
    SnakeRenderer& getSnakeRenderer();

    void setNetworkGenome(Genome &genome);
};


#endif //SNAKEAI_RENDERER_HPP
