//
// Created by oscar on 17/07/2024.
//

#ifndef SNAKEAI_STATSRENDERER_HPP
#define SNAKEAI_STATSRENDERER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <format>
#include "../../config.hpp"
#include "card.hpp"
#include "textutils.hpp"

using namespace sf;
using namespace std;

class StatsRenderer {
    // Death reasons section
    VertexArray starvationLine;
    VertexArray collisionLine;
    VertexArray suicideLine;
    VertexArray wonLine;

public:
    void render(RenderWindow &window, Font &font, const vector<vector<int>> &deathReasonsCount);

    static void drawBackground(RenderWindow &window);
    static void drawLegend(RenderWindow &window, Font &font);
    static void drawGraphTitle(RenderWindow &window, Font &font);
    static void drawNumberOfAnalysedGames(RenderWindow &window, Font &font, uint64_t numberOfAnalysedGames);

    void updateLines(const vector<vector<int>>& deathReasonsCount);
    void resetLines();

    void drawLines(RenderWindow &window);
};


#endif //SNAKEAI_STATSRENDERER_HPP
