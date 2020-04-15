#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <list>
#include "gameBoard.h"

class Snake {
	std::list<Cell> snakeBody;
	Cell head;

public:
	Snake(int x=2, int y=2, int length = 3);
	void grow(Cell);
};

#endif //SNAKE_SNAKE_H