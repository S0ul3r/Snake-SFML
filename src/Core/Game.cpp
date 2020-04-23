#include <windows.h>
#include "Game.h"

Game::Game(int width, int height){
	board = Board(width, height);
	snake  = Snake(int(height/2), int(width/3));
	dir = direction::DIR_RIGHT;
	for(auto it = snake.getTail();it != snake.getEnd(); ++it){
		board.setType(it->getCellX(), it->getCellY(), it->getCellType());
	}
}


void Game::update(){

	for(int i=0; i<board.width; i++ ){
		for(int j =0; j<board.height; j++){
			if(board.getType(i, j) != cellType::SNAKE)
				board.setType(i, j, board.getType(i, j));
			else{
				board.setType(i, j, cellType::EMPTY);
			}
		}
	}

	for(auto it = snake.getTail();it != snake.getEnd(); ++it){
		board.setType(it->getCellX(), it->getCellY(), it->getCellType());
	}
}

void Game::display(){
	board.debug_display();
	snake.printSnake();
}

void Game::run(){
	while(true){
		update();
		display();
		Sleep(4000);
	}
}