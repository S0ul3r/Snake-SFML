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
	Game(int width, int height);
	void move();
	void display()const;
};

#endif //SNAKE_GAME_H