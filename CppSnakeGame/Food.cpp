#include "Food.h"
#include <iostream>

Food::Food(int pSize) {
	this->pSize = pSize;
	this->cell = FoodCell();
}

void Food::render(sf::RenderWindow &window) {
	window.draw(this->cell.shape);
}

void Food::generateFood(sf::RenderWindow &window, Board *board) {

	std::vector<Board::BoardCell> emptyCells;
	std::vector<std::vector<Board::BoardCell>> canvas = board->getBoard();
	std::vector<Board::BoardCell*> freeCells;

	//TODO: can make this faster, by keeping a track of 
	// empty cells during snake movement
	for (int i = 0; i < canvas.size(); i++) {
		for (int j = 0; j < canvas[i].size(); j++) {

			if (canvas[i][j].isEmpty && !canvas[i][j].isWall) {
				freeCells.push_back(&canvas[i][j]);
			}

		}
	}


	// Providing a seed value
	srand((unsigned)time(NULL));

	// Get a random number
	int random = rand() % freeCells.size() + 0;


	sf::RectangleShape rect;
	rect.setSize({ (float) this->pSize, (float) this->pSize });
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(freeCells[random]->pos * (float) pSize);

	this->cell.shape = rect;
	this->cell.pos = freeCells[random]->pos * (float) pSize;

	this->eaten = false;

}