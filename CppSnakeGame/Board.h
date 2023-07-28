#pragma once
#include <SFML/Graphics.hpp>

class Board {

public:

	struct BoardCell {
		bool isWall;
		bool isEmpty;
		sf::Vector2f pos;
		sf::RectangleShape shape;

		BoardCell() {
			this->isWall = false;
			this->isEmpty = true;
			pos = { 0.f, 0.f };
		}
	};

private:
	std::vector<std::vector<BoardCell>> board;
	int rows;
	int cols;
	int pHeight;
	int pWidth;



public:

	Board(int rows, int cols, int pHeight, int pWdith);
	std::vector<std::vector<BoardCell>> getBoard() { return this->board; }

	void render(sf::RenderWindow&);

	int getRowCount() { return this->rows; }
	int getColCount() { return this->cols; }

	
private:
	
	void init();

};