#include "Snake.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


sf::RectangleShape generatePart(int pHeight, int pWidth, Snake::SnakeCell cell) {

	sf::RectangleShape rect(sf::Vector2f(10, 10));
	rect.setSize(sf::Vector2f(pHeight, pWidth));

	if (cell.isHead)
		rect.setFillColor(sf::Color::Magenta);

	else rect.setFillColor(sf::Color::Cyan);

	rect.setPosition(cell.pos * (float)pHeight);;

	return rect;
}

Snake::Snake(int windowSize, int length, int pSize, float updateTime) {

	this->length = length;
	this->pSize = pSize;
	this->dir = { 0.f, 1.f };
	this->timestep = 5.f / 60;
	this->updateTime = updateTime;
	this->windowSize = windowSize;
	this->dirApplied = false;
	
	this->init();
}

void Snake::grow() {
	SnakeCell cell;
	cell.isHead = false;
	int size = this->body.size();
	cell.pos = this->body[size - 1].pos;
	cell.shape = generatePart(this->pSize, this->pSize, cell);

	this->body.push_back(cell);
}

void Snake::move(std::vector<std::vector<Board::BoardCell>> canvas) {

	SnakeCell head = this->body[0];
	SnakeCell cell;

	cell.pos = head.pos + (this->dir);
	
	this->dirApplied = true;

	cell.isHead = true;
	cell.shape = generatePart(this->pSize, this->pSize, cell);
	
	
	this->body[0].isHead = false;
	this->body[0].shape.setFillColor(sf::Color::Cyan);
	
	this->body.insert(this->body.begin() + 0, cell);
	
	SnakeCell tail = this->body[this->body.size() - 1];

	this->body.pop_back();

}
void Snake::init() {
	
	sf::Vector2f startingPos(10.f, 10.f);

	for (int i = 0; i < length; i++) {
		SnakeCell cell;

		
		cell.pos = startingPos;
		
		if (i == 0) cell.isHead = true;
		else cell.isHead = false;

		cell.shape = generatePart(this->pSize, this->pSize, cell);

		startingPos.y--;
		this->body.push_back(cell);
	}

	this->body[0].isHead = true;

}


void Snake::setDirection(float x, float y) {
	if (!this->dirApplied) return;

	this->dirApplied = false;
	
	if (y == 1.f && this->dir.y != -1.f){
		this->dir.y = y;
		this->dir.x = 0.f;
	}
	else if (y == -1.f && this->dir.y != 1.f) {
		this->dir.y = y;
		this->dir.x = 0.f;
	}
	else if (x == 1.f && this->dir.x != -1.f) {
		this->dir.x = x;
		this->dir.y = 0.f;
	}
	else if (x == -1.f && this->dir.x != 1.f) {
		this->dir.x = x;
		this->dir.y = 0.f;
	}
	//std::cout << "Moving " << this->dir.x << " -- " << this->dir.y << std::endl;
	
}

void Snake::render(sf::RenderWindow &window) {
	
	for (int i = 0; i < this->body.size(); i++) {
		this->body[i].shape.setPosition(this->body[i].pos * (float)this->pSize);
		window.draw(this->body[i].shape);
	}
}


void Snake::eat(Food *food) {
	//std::cout << "INTERACTS " << this->body[0].shape.getGlobalBounds().intersects(food->cell.shape.getGlobalBounds()) << std::endl;
	if (this->body[0].shape.getGlobalBounds().intersects( food->cell.shape.getGlobalBounds())) {
		food->eaten = true;
		this->grow();
		this->updateTime -= 2;
	}

}