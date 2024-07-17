//
// Created by oscar on 17/07/2024.
//

#include "headers/statsrenderer.hpp"

void StatsRenderer::render(RenderWindow &window, Font &font, const vector<vector<int>> &deathReasonsCount) {
    drawBackground(window);
    updateLines(deathReasonsCount);
    drawLines(window);
    drawLegend(window, font);
    drawGraphTitle(window, font);
    drawNumberOfAnalysedGames(window, font, deathReasonsCount.size() * config::genetic::populationSize * config::genetic::numberOfGamesPerAgent);
}

void StatsRenderer::drawBackground(sf::RenderWindow &window) {
    Card::makeAndDrawWithCheckedPattern(window, Vector2i(config::layout::stats::originX, config::layout::stats::originY),
                                        Vector2i(config::layout::stats::width, config::layout::stats::height),
                                        config::colors::darkerBgColor, 2, Color::White,
                                        10, 10, config::colors::bgColor);
}

void StatsRenderer::updateLines(const vector<vector<int>>& deathReasonsCount) {
    constexpr float x = config::layout::stats::originX;
    constexpr float y = config::layout::stats::originY;
    constexpr float width = config::layout::stats::width;
    constexpr float height = config::layout::stats::height;
    constexpr float max = config::genetic::populationSize * config::genetic::numberOfGamesPerAgent;

    resetLines();
    for (size_t i = 0; i <  deathReasonsCount.size(); ++i) {
        float xPos = x + (i * width / (deathReasonsCount.size() - 1));
        float yPos = height - deathReasonsCount[i][0] / max * height;
        starvationLine.append(Vertex(Vector2f(xPos, y + yPos), config::colors::stats::starvationColor));

        yPos = height - deathReasonsCount[i][1] / max * height;
        collisionLine.append(Vertex(Vector2f(xPos, y + yPos), config::colors::stats::collisionColor));

        yPos = height - deathReasonsCount[i][2] / max * height;
        suicideLine.append(Vertex(Vector2f(xPos, y + yPos), config::colors::stats::suicideColor));

        yPos = height - deathReasonsCount[i][3] / max * height;
        wonLine.append(Vertex(Vector2f(xPos, y + yPos), config::colors::stats::wonColor));
    }
}

void StatsRenderer::drawLines(RenderWindow &window) {
    window.draw(starvationLine);
    window.draw(collisionLine);
    window.draw(suicideLine);
    window.draw(wonLine);
}

void StatsRenderer::resetLines() {
    starvationLine.clear();
    starvationLine.setPrimitiveType(LineStrip);
    collisionLine.clear();
    collisionLine.setPrimitiveType(LineStrip);
    suicideLine.clear();
    suicideLine.setPrimitiveType(LineStrip);
    wonLine.clear();
    wonLine.setPrimitiveType(LineStrip);
}

void StatsRenderer::drawLegend(RenderWindow &window, Font &font) {
    const float outlineThickness = 1;
    const Color outlineColor = Color::White;
    const float x = config::layout::stats::originX + 5;
    const float y = config::layout::stats::originY;
    const Vector2f cardSize = Vector2f(8, 8);
    const int charSize = 10;
    const float textYOffset = -2;
    const float vGap = 5;
    RectangleShape starvationLegend = Card::make(Vector2f(x, y + 20), cardSize,
                                                 config::colors::stats::starvationColor, outlineThickness, outlineColor);
    RectangleShape collisionLegend = Card::make(Vector2f(x, starvationLegend.getPosition().y + starvationLegend.getSize().y + vGap),
                                                cardSize, config::colors::stats::collisionColor, outlineThickness, outlineColor);
    RectangleShape suicideLegend = Card::make(Vector2f(x, collisionLegend.getPosition().y + collisionLegend.getSize().y + vGap),
                                                cardSize, config::colors::stats::suicideColor, outlineThickness, outlineColor);
    RectangleShape wonLegend = Card::make(Vector2f(x, suicideLegend.getPosition().y + suicideLegend.getSize().y + vGap),
                                            cardSize, config::colors::stats::wonColor, outlineThickness, outlineColor);
    window.draw(starvationLegend);
    window.draw(collisionLegend);
    window.draw(suicideLegend);
    window.draw(wonLegend);
    Text starvationText = TextUtils::make("Starvation", charSize, config::colors::textColor,
                                          Vector2f(x + cardSize.x + 5, starvationLegend.getPosition().y + textYOffset),
                                          font);
    Text collisionText = TextUtils::make("Collision", charSize, config::colors::textColor,
                                         Vector2f(x + cardSize.x + 5, collisionLegend.getPosition().y + textYOffset),
                                         font);
    Text suicideText = TextUtils::make("Suicide", charSize, config::colors::textColor,
                                       Vector2f(x + cardSize.x + 5, suicideLegend.getPosition().y + textYOffset), font);
    Text wonText = TextUtils::make("Won", charSize, config::colors::textColor,
                                   Vector2f(x + cardSize.x + 5, wonLegend.getPosition().y + textYOffset), font);
    window.draw(starvationText);
    window.draw(collisionText);
    window.draw(suicideText);
    window.draw(wonText);
}

void StatsRenderer::drawGraphTitle(RenderWindow &window, Font &font) {
    Text title = TextUtils::make("Death reasons", 10, config::colors::textColor,
                                 Vector2f(config::layout::stats::originX + 5, config::layout::stats::originY + 5),
                                 font);
    window.draw(title);
}

void StatsRenderer::drawNumberOfAnalysedGames(RenderWindow &window, Font &font, uint64_t numberOfAnalysedGames) {
    const string textToWrite = format("{} analyzed games", numberOfAnalysedGames);
    Text txt = TextUtils::make(textToWrite, 10, config::colors::textColor,
                               Vector2f(config::layout::stats::originX + config::layout::stats::width,
                                        config::layout::stats::originY + config::layout::stats::height), font);
    txt.setOrigin(txt.getLocalBounds().width + 5, txt.getLocalBounds().height + 5);
    window.draw(txt);
}
