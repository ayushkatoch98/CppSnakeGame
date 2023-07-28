#pragma once
#include "Game.h"
#include <iostream>
#include <string>
#include "Button.h"

#define SNAKE_LENGTH 5

Game::Game(int windowSize, int scoreSize, int rows, int cols, sf::Font &font) {
    windowSize -= scoreSize;
    this->running = true;
    this->showingMainMenu = false;
    this->score = 0;
    this->pSize = windowSize / rows;

    this->rows = rows;
    this->cols = cols;

    this->windowSize = windowSize;
    this->scoreSize = scoreSize;

    this->font = font;
    this->board = new Board(rows, cols, this->pSize, this->pSize);
    this->snake = new Snake(windowSize, SNAKE_LENGTH, this->pSize, 100);
    this->food = new Food(this->pSize);
    
    this->buttonPlay.setText("The\nSname");
    this->buttonPlay.setWindowSize(this->windowSize);
    this->buttonPlay.setFont(this->font);

   
}

void Game::reset() {
    delete this->board;
    delete this->snake;
    delete this->food;


    this->score = 0;

    this->running = false;
    this->showingMainMenu = true;
    this->board = new Board(this->rows, this->cols, this->pSize, this->pSize);
    this->snake = new Snake(windowSize, SNAKE_LENGTH, this->pSize, 100);
    this->food = new Food(this->pSize);

    this->food->eaten = true;



}
bool Game::checkCollision(Snake* snake, Board* board) {

    std::vector<Snake::SnakeCell> body = snake->getBody();
    Snake::SnakeCell head = body[0];

    int snakeLen = body.size();
    int rows = board->getRowCount();
    int cols = board->getColCount();
    std::vector<std::vector<Board::BoardCell>> canvas = board->getBoard();
    int tempCols;

    // snake body collision

    for (int i = 1; i < snakeLen; i++) {
        if (head.shape.getGlobalBounds().intersects(body[i].shape.getGlobalBounds())) {
            //std::cout << "SNAKE HEAD Collision Index " << i << std::endl;
            return true;
        }
    }

    // wall collision 
    //sf::Vector2f headPosition = head.pos;
    //std::cout << "Head Position " << head.pos.x << " | " << head.pos.y << std::endl;
    if (head.pos.x == 0.f || head.pos.y == 0.f || head.pos.x == cols - 1 || head.pos.y == rows - 1)
        return true;


    return false;

}


void Game::renderScore(sf::RenderWindow &window, int score) {

    sf::Text text;
    text.setFont(this->font);
    text.setString("Score: " + std::to_string(score));
    text.setFillColor(sf::Color::White);
    text.setPosition({ 0.f , (float) this->windowSize + 2.f });

    window.draw(text);

}

void Game::renderGameOverScreen(sf::RenderWindow& window) {

    sf::Text text;
    text.setFont(this->font);
    text.setString("Game Over");
    text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    text.setPosition(sf::Vector2f(this->windowSize / 2.0f, this->windowSize / 2.0f));

    window.draw(text);

}

void Game::renderMainMenu(sf::RenderWindow& window) {


    sf::Vector2f pos = { this->windowSize / 2.0f, this->windowSize / 2.0f };
    this->buttonPlay.setPosition(pos);
    this->buttonPlay.render(window);

}

void Game::start(sf::RenderWindow& window) {

    this->food->generateFood(window, this->board);

    sf::Clock clock;
    sf::Time time;

    window.setFramerateLimit(60u);

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::X))
                window.close();

            if (this->showingMainMenu) {
                if (this->buttonPlay.isClicked(window)) {

                    this->showingMainMenu = false;
                    this->running = true;

                }
            }

            if (!this->running) continue;
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                this->snake->setDirection(-1.f, 0.f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                this->snake->setDirection(1.f, 0.f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                this->snake->setDirection(0.f, -1.f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                this->snake->setDirection(0.f, 1.f);
            }
        }

      
        window.clear();

        if (this->food->eaten) {
            this->food->generateFood(window, this->board);
            this->food->render(window);
        }

        if (this->showingMainMenu) {
            this->renderMainMenu(window);
        }


        else if (this->running) {

            time = clock.getElapsedTime();
            if (time.asMilliseconds() >= this->snake->getUpdateTime()) {
                clock.restart();

                this->snake->move(this->board->getBoard());

                this->snake->eat(this->food);

                if (this->checkCollision(this->snake, this->board)) {
                    this->running = false;
                }
             
                if (this->food->eaten) {
                    this->food->generateFood(window, this->board);
                    this->score++;
                }

               

            }


            this->renderScore(window, this->score);
            this->board->render(window);
            this->snake->render(window);
            this->food->render(window);

        }
      
        else {
            // Game Over
            this->renderGameOverScreen(window);
            this->reset();
        }

        
        window.display();
    }
}