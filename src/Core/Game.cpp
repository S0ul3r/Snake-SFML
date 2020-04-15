#include "Game.h"

Game::Game(int width, int height){
	board = Board(width, height);
	snake  = Snake(int(height/2), int(width/3));
	dir = direction::DIR_RIGHT;
}


void Game::move(){

}

void update(){
	std::list<Cell>::iterator it =
	for()

}

void Game::display()const{

}