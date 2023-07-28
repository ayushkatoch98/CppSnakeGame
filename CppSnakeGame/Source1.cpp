class Snake {

private:
	int length;
	int** board;
	int boardSize;

public:

	Snake(int** board, int boardSize) {
		this->board = board;
		this->boardSize = boardSize;
	}

	void move(int x, int y) {

	}

	void eat() {
		this->length++;
	}



};