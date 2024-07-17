//
// Created by oscar on 06/07/2024.
//

#ifndef PENDULUMBALANCERAI_BUTTON_HPP
#define PENDULUMBALANCERAI_BUTTON_HPP
#include "../../config.hpp"

class Button {
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Font font;
public:
    Button(float x, float y, float width, float height, const std::string& text, sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool isMouseOver(sf::RenderWindow& window);
};


#endif //PENDULUMBALANCERAI_BUTTON_HPP
