//
// Created by oscar on 06/07/2024.
//

#include "headers/button.hpp"

Button::Button(float x, float y, float width, float height, const std::string& text, sf::Font& font) {
    buttonShape.setPosition(x, y);
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonShape.setFillColor(config::colors::buttons::normal);
    buttonShape.setOutlineThickness(2);
    buttonShape.setOutlineColor(config::colors::buttons::outline);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);

    // Center text on the button
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(x + width / 2.0f, y + height / 2.0f);
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(buttonShape);
    window.draw(buttonText);
}

bool Button::isMouseOver(sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    return buttonShape.getGlobalBounds().contains(mousePosF);
}

