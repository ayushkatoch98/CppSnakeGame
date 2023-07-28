#include "Button.h"
#include <iostream>

Button::Button() {

}
Button::Button(std::string text, int windowSize, sf::Font font) {
    this->text = text;
    this->windowSize = windowSize;
    this->font = font;

    this->textElement.setFont(this->font);
    this->textElement.setString("The\nSnake");
    this->textElement.setFillColor(sf::Color::White);

}

void Button::setText(std::string text) {
    this->text = text;
    this->textElement.setString("The\nSnake");
}

void Button::setFont(sf::Font font) {
    this->font = font;
    this->textElement.setFont(this->font);
}

void Button::setWindowSize(int windowSize) {
    this->windowSize = windowSize;
}

void Button::render(sf::RenderWindow& window) {
  
    window.draw(this->textElement);
}

void Button::setPosition(sf::Vector2f pos) {
    sf::FloatRect textRect = this->textElement.getLocalBounds();
    this->textElement.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    this->textElement.setPosition(pos);

}

bool Button::isClicked(sf::RenderWindow& window) {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window

        if (this->textElement.getGlobalBounds().contains((float)localPosition.x, (float)localPosition.y)){
            return true;
        }

        return false;

    }
}

