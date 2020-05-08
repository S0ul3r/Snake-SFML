#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "Snake.h"

enum direction{
	DIR_NONE = 0,
	DIR_RIGHT = 1,
	DIR_LEFT = -1,
	DIR_UP = 2,
	DIR_DOWN = -2,
};

class Game{
	Snake snake;
	Board board;
	direction dir;

public:
	int width;
	int height;
	Game(int width, int height);
	void display();
	void update();
	void run();
	Cell nextCell();
	cellType getType(int , int);
	direction getDirection();
	void setDirection(direction);
	void placeFood();
};

#endif //SNAKE_GAME_H