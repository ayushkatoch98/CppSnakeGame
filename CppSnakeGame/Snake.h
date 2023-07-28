#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Board.h"
#include "Food.h"

class Snake {
public:
	struct SnakeCell {
		sf::Vector2f pos;
		int index;
		bool isHead;
		sf::RectangleShape shape;

		SnakeCell() {
			this->pos = { 0.f, 0.f };
			this->index = 0;
			this->isHead = false;
		}
	};

private:
	int length;
	int pSize;
	int windowSize;
	float timestep;
	sf::Vector2f dir;
	float updateTime;
	std::vector<SnakeCell> body;
	bool dirApplied;


	void grow();
	
public:


	Snake(int windowSize, int length, int pSize, float updateTime);


	void move(std::vector<std::vector<Board::BoardCell>> canvas);

	void init();

	void setDirection(float x, float y);

	void render(sf::RenderWindow& window);

	std::vector<SnakeCell> getBody() { return this->body; }

	float getUpdateTime() { return this->updateTime; }

	void eat(Food *food);

};