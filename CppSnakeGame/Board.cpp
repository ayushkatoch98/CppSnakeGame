#pragma once
#include "Board.h"
#include <iostream>


sf::RectangleShape getBlankRect(int pHeight, int pWidth, int i, int j) {
	sf::RectangleShape rect(sf::Vector2f(pHeight, pWidth));
	rect.setSize(sf::Vector2f(pHeight, pWidth));
	//rect.setOutlineThickness(1.f);
	rect.setOutlineColor(sf::Color::White);
	rect.setFillColor(sf::Color::Black);
	rect.setPosition(sf::Vector2f(pHeight * i, pWidth * j));

	return rect;
}


sf::RectangleShape getWallRect(int pHeight, int pWidth, int i, int j) {
	sf::RectangleShape rect(sf::Vector2f(pHeight, pWidth));
	rect.setSize(sf::Vector2f(pHeight, pWidth));
	//rect.setOutlineThickness(1.f);
	rect.setOutlineColor(sf::Color::Red);
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(sf::Vector2f(pHeight * i, pWidth * j));

	return rect;
}


Board::Board(int rows, int cols, int pHeight, int pWdith){
	this->rows = rows;
	this->cols = cols;
	this->pHeight = pHeight;
	this->pWidth = pWdith;
	this->init();
}


void Board::init() {

	for (int i = 0; i < this->rows; i++) {
		
		std::vector<BoardCell> col(cols);
		this->board.push_back( col );
		for (int j = 0; j < this->cols; j++) {

			if (i == 0 || i == this->rows - 1 || j == 0 || j == this->cols - 1) {
				this->board[i][j].isWall = true;
				this->board[i][j].shape = getWallRect(this->pHeight, this->pWidth, i, j);
			}
			else {
				this->board[i][j].shape = getBlankRect(this->pHeight, this->pWidth, i, j);
			}

			this->board[i][j].pos = { (float) i, (float) j };
			
		}
	}		
}


void Board::render(sf::RenderWindow& window) {

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			window.draw(this->board[i][j].shape);
		}
	}

}