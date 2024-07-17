//
// Created by oscar on 14/07/2024.
//

#include "headers/networkrenderer.hpp"

NetworkRenderer::NetworkRenderer(Genome &genome) : genome(genome) {}

void NetworkRenderer::render(sf::RenderWindow &window) {
    calculateNodesPositions();
    drawBackground(window);
    drawConnections(window);
    drawNodes(window);
}

void NetworkRenderer::drawBackground(sf::RenderWindow &window) {
    RectangleShape bg = Card::make(Vector2i(config::layout::net::originX, config::layout::net::originY),
                                    Vector2i(config::layout::net::width, config::layout::net::height),
                                    config::colors::darkerBgColor, 2, Color::White);
    window.draw(bg);
}

void NetworkRenderer::setGenome(const Genome &gen) {
    NetworkRenderer::genome = gen;
}

void NetworkRenderer::calculateNodesPositions() {
    int depth = genome.getDepth();
    nodesPositions.clear();
    float xSpacing = (float) allowedSpace.x / (float) (depth + 1);
    for (int i = 0; i < depth; i++) {
        std::vector<Node> nodes = genome.getNodesInLayer(i);
        float ySpacing = (float) allowedSpace.y / (float) (nodes.size() + 1);
        for (int j = 0; j < nodes.size(); j++) {
            float x = (float) (i + 1) * xSpacing + origin.x;
            float y = (float) (j + 1) * ySpacing + origin.y;
            nodesPositions[nodes[j].id] = Vector2f(x, y);
        }
    }
}

void NetworkRenderer::drawNodes(sf::RenderWindow &window) {
    for (auto & nodesPosition : nodesPositions) {
        Vector2f position = nodesPosition.second;
        drawNode(window, position.x, position.y);
    }
}

void NetworkRenderer::drawNode(sf::RenderWindow &window, float xPos, float yPos) {
    sf::CircleShape node(config::netrender::nodeRadius);
    node.setFillColor(config::colors::net::nodeColor);
    node.setOutlineThickness(config::netrender::nodeOutlineThickness);
    node.setOutlineColor(config::colors::net::nodeOutlineColor);
    node.setPosition(xPos, yPos);
    window.draw(node);
}

void NetworkRenderer::drawConnections(sf::RenderWindow &window) {
    for (Connection connection : genome.getConnections()) {
        float fromX = nodesPositions[connection.from].x + config::netrender::nodeRadius;
        float fromY = nodesPositions[connection.from].y + config::netrender::nodeRadius;
        float toX = nodesPositions[connection.to].x + config::netrender::nodeRadius;
        float toY = nodesPositions[connection.to].y + config::netrender::nodeRadius;
        sf::RectangleShape line = drawConnection(Vector2f(fromX, fromY), Vector2f(toX, toY), connection.weight);
        window.draw(line);
    }
}

sf::RectangleShape NetworkRenderer::drawConnection(sf::Vector2f from, sf::Vector2f to, float thickness) {
    sf::Vector2f direction = to - from;
    float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    thickness *= config::netrender::maximumConnectionThickness;
    thickness = std::max(config::netrender::minimumConnectionThickness, thickness);

    sf::RectangleShape connection(sf::Vector2f(length, thickness));
    connection.setFillColor(config::colors::net::connectionColor);
    connection.setPosition(Vector2f(from.x, from.y - thickness / 2));

    float angle = atan2(direction.y, direction.x) * 180 / M_PI;
    connection.setRotation(angle);

    return connection;
}

NetworkRenderer::NetworkRenderer() = default;