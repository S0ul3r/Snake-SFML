#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "Game.h"

//Constructor
Game::Game(int width, int height){
	board = Board(width, height);
	snake  = Snake(int(height/2), int(width/3));
	dir = direction::DIR_RIGHT;
	for(auto it = snake.getTail();it != snake.getEnd(); ++it){
		board.setType(it->getCellX(), it->getCellY(), it->getCellType());
	}
	this->width = width;
	this->height = height;
	placeFood();
}

//Updating board on every move (will determine difficulty)
void Game::update(){
	Cell c = nextCell();
	snake.move(c);

	if(c.getCellType() == cellType::FOOD){
		placeFood();
		board.setType(c.getCellX(), c.getCellY(), cellType::EMPTY);
	}
	//Clearing board from snake
	for(int i=0; i<board.width; i++ ){
		for(int j =0; j<board.height; j++){
			if(board.getType(i, j) == cellType::SNAKE)
				board.setType(i, j, cellType::EMPTY);
		}
	}

	//Creating new snake body
	for(auto it = snake.getTail();it != snake.getEnd(); ++it){
		board.setType(it->getCellX(), it->getCellY(), cellType::SNAKE);
	}
}

//Determine which cell is next using direction
Cell Game::nextCell() {
	auto head = snake.getHead();
	int x = head->getCellX();
	int y = head->getCellY();

	if (dir == 1) {
		y += 1;
	} else if (dir == 2) {
		x -= 1;
	} else if (dir == -1) {
		y -= 1;
	} else if (dir == -2) {
		x += 1;
	}
	return board.getCell(x, y);
}

//Better display
void Game::display(){
	board.debug_display();
	snake.printSnake();
}

//Infinite game loop
void Game::run(){
	while(true){
		update();
		display();
	}
}

//Place food randomly
void Game::placeFood(){
	std::vector<Cell> v;
	for(int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			if(board.getType(i,j) == cellType::EMPTY){
				v.push_back(board.getCell(i,j));
			}
		}
	}
	if(v.size()> 0){
		std::srand(std::time(0));
		std::random_shuffle(v.begin(), v.end());
		board.setType(v[0].getCellX(),v[0].getCellY(), cellType::FOOD);
	}
}

//Setters and getters
cellType Game::getType(int i, int j){
	return board.getType(i,j);
}

direction Game::getDirection(){
	return dir;
}

void Game::setDirection(direction d){
	dir = d;
}