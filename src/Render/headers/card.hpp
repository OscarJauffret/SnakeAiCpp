//
// Created by oscar on 11/07/2024.
//
#ifndef PENDULUMBALANCERAI_CARD_HPP
#define PENDULUMBALANCERAI_CARD_HPP
#include <SFML/Graphics.hpp>
using namespace sf;

class Card {
public:

    /**
     * Creates a rectangle shape with the specified parameters
     * @param position The position of the card
     * @param size The size of the card
     * @param color The background color of the card
     * @param outlineThickness The thickness of the outline
     * @param outlineColor The color of the outline
     * @return
     */
    static RectangleShape make(Vector2f position, Vector2f size, Color color, float outlineThickness, Color outlineColor) {
        RectangleShape card(size);
        card.setPosition(position);
        card.setFillColor(color);
        card.setOutlineThickness(outlineThickness);
        card.setOutlineColor(outlineColor);
        return card;
    }

    /**
     * Creates a rectangle shape with the specified parameters
     * @param position The position of the card
     * @param size The size of the card
     * @param color The background color of the card
     * @param outlineThickness The thickness of the outline
     * @param outlineColor The color of the outline
     * @return
     */
    static RectangleShape make(Vector2i position, Vector2i size, Color color, float outlineThickness, Color outlineColor) {
        Vector2f sizeF = Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
        Vector2f positionF = Vector2f(static_cast<float>(position.x), static_cast<float>(position.y));
        RectangleShape card(sizeF);
        card.setPosition(positionF);
        card.setFillColor(color);
        card.setOutlineThickness(outlineThickness);
        card.setOutlineColor(outlineColor);
        return card;
    }

    /**
     * Creates a rectangle shape with the specified parameters and draws it, this card has a checked pattern
     * @param window The window where the card will be drawn
     * @param position The position of the card
     * @param size The size of the card
     * @param color The background color of the card
     * @param outlineThickness The thickness of the outline
     * @param outlineColor The color of the outline
     * @param numberOfVerticalLines The number of vertical lines
     * @param numberOfHorizontalLines The number of horizontal lines
     * @param lineColor The color of the lines
     */
    static void makeAndDrawWithCheckedPattern(RenderWindow &window, Vector2i position, Vector2i size, Color color,
                                              float outlineThickness, Color outlineColor, int numberOfVerticalLines,
                                              int numberOfHorizontalLines, Color lineColor) {
        RectangleShape card = make(position, size, color, outlineThickness, outlineColor);
        window.draw(card);
        for (int i = 0; i < numberOfVerticalLines; i++) {
            RectangleShape line(Vector2f(1, size.y));
            line.setPosition(position.x + i * size.x / numberOfVerticalLines, position.y);
            line.setFillColor(lineColor);
            window.draw(line);
        }
        for (int i = 0; i < numberOfHorizontalLines; i++) {
            RectangleShape line(Vector2f(size.x, 1));
            line.setPosition(position.x, position.y + i * size.y / numberOfHorizontalLines);
            line.setFillColor(lineColor);
            window.draw(line);
        }
    }
};

#endif //PENDULUMBALANCERAI_CARD_HPP