#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
	std::string text;
	sf::Vector2f pos;
	sf::Text textElement;
	sf::Font font;
	int windowSize;

public:

	Button();
	Button(std::string text, int windowSize, sf::Font font);

	void setText(std::string text);

	void setFont(sf::Font font);

	void setWindowSize(int windowSize);

	void render(sf::RenderWindow& window);

	void setPosition(sf::Vector2f pos);

	bool isClicked(sf::RenderWindow& window);

};