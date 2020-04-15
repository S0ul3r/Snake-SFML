#include "Snake.h"

Snake::Snake(int x, int y, int length){
	snakeBody.push_front(Cell(x, y, cellType::SNAKE));
	for(int i=0;i<length -1;i++){
		snakeBody.push_front(Cell(x, y-i, cellType::SNAKE));
	}
	std::list<Cell>::iterator head = snakeBody.end();
	head--;

}

void Snake::grow(Cell c){
	snakeBody.push_back(c);
}

