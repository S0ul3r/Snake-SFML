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
	Board board;
	direction dir;
	gameState state;
	Snake snake;
	int score;

public:
	int width;
	int height;
	Game(int width, int height);
	void display();
	void update();
	void run();
	Cell nextCell();
	void placeFood();
	cellType getType(int , int);
	direction getDirection();
	void setDirection(direction);
	gameState getGamestate();
	void setGamestate(gameState);
	int getScore();
};

#endif //SNAKE_GAME_H