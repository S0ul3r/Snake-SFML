#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <list>
#include "gameBoard.h"

class Snake {
	std::list<Cell> snakeBody;
	std::list<Cell>::iterator head;
	std::list<Cell>::iterator tail;

public:
	Snake(int x=2, int y=2, int length = 3);
	void move(Cell);
	void printSnake();
	std::list<Cell>::iterator getHead()const;
	std::list<Cell>::iterator getTail()const;
	std::list<Cell>::iterator getEnd();
	bool stateOfGame;
};

#endif //SNAKE_SNAKE_H