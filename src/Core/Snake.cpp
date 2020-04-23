#include <iostream>
#include "Snake.h"

Snake::Snake(int x, int y, int length){
	snakeBody.push_back(Cell(x, y, cellType::SNAKE));
	for(int i=1;i<length ;i++){
		snakeBody.push_front(Cell(x, y-i, cellType::SNAKE));
	}
	std::list<Cell>::iterator head = snakeBody.end();
	head--;
	this->head = head;
	std::list<Cell>::iterator tail = snakeBody.begin();
	this->tail = tail;
	state = gameState::RUNNING;
}


void Snake::move(Cell c){
	if(c.getCellType() == cellType::FOOD){
		snakeBody.push_back(c);
	}else if(c.getCellType() == cellType::EMPTY){
		snakeBody.push_back(c);
		snakeBody.pop_front();
	}else if(c.getCellType() == cellType::SNAKE){
		Cell  x = snakeBody.front();
		if(x.getCellX() == c.getCellX() && x.getCellY() == c.getCellY()){
			snakeBody.push_back(c);
			snakeBody.pop_front();
		}else{
			state = gameState::LOSE;
		}
	}else if(c.getCellType() == cellType::WALL){
		state = gameState::LOSE;
	}
	this->head = snakeBody.end();
	this->head--;
	this->tail = snakeBody.begin();
}

std::list<Cell>::iterator Snake::getHead()const{
	return head;
}

std::list<Cell>::iterator Snake::getTail()const{
	return tail;
}

std::list<Cell>::iterator Snake::getEnd(){
	return snakeBody.end();
}

void Snake::printSnake(){
	for(auto it = getTail();it != getEnd(); ++it){
		std::cout<<it->getCellX()<<"   "<<it->getCellY()<<"  "<<it->getCellType()<<"\n";
	}
}