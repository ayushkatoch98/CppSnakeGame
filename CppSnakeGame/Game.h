#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Food.h"
#include "Snake.h"
#include "Button.h"


class Game {

private:
    int score;
    bool running;
    bool showingMainMenu;
    int pSize;
    int rows;
    int cols;
    sf::Font font;
    Board* board;
    Snake* snake;
    Food* food;
    int windowSize;
    int scoreSize;
    Button buttonPlay;

public:

    Game(int windowSize, int scoreSize, int rows, int cols, sf::Font &font);

    void reset();

    bool checkCollision(Snake* snake, Board* board);

    void renderScore(sf::RenderWindow& window, int score);

    void renderGameOverScreen(sf::RenderWindow& window);

    void renderMainMenu(sf::RenderWindow& window);

    void start(sf::RenderWindow& window);

};