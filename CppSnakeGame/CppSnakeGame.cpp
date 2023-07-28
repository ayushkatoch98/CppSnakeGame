#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

#define WINDOW_SIZE 550
#define BOARD_SIZE 50
#define SCORE_SIZE 50


int main(){

    if (WINDOW_SIZE % 2 != 0 || BOARD_SIZE % 2 != 0) {
        std::cout << "Board and Window size must be an even number" << std::endl;
        return 1;
    }

    if (WINDOW_SIZE % BOARD_SIZE != 0) {
        std::cout << "Board and Window size must be divisible" << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE - SCORE_SIZE, WINDOW_SIZE), "Snake Game");

    sf::Font font;
    if (!font.loadFromFile("valorax.otf")) {
        std::cout << "Unable to load font";
        window.close();
        return 1;
    }
 
    Game game(WINDOW_SIZE, SCORE_SIZE, BOARD_SIZE, BOARD_SIZE, font);

    game.start(window);

    return 0;
}