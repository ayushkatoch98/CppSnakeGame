#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Food {
public:
	struct FoodCell {
		sf::Vector2f pos;
		sf::RectangleShape shape;

		FoodCell() {
			this->pos = { 0.f, 0.f };
		}


	};

	bool eaten = false;

	FoodCell cell;
private:

	int pSize;

public:
	Food(int pSize);
	void render(sf::RenderWindow& window);
	void generateFood(sf::RenderWindow &window, Board *board);
};
