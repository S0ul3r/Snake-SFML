#ifndef SNAKE_CELL_H
#define SNAKE_CELL_H

enum cellType {
	EMPTY,
	WALL,
	SNAKE,
	FOOD,
};

enum gameState {
	RUNNING,
	WIN,
	LOSE
};

class Cell {
	int x;
	int y;
	cellType type;

public:
	Cell(int x = 0, int y = 0, cellType t = cellType::EMPTY):x(x),y(y),type(t){}

	void setX(int x){this->x = x;}
	void setY(int y){this->y = y;}
	void setType(cellType t){this->type = t;}
	int getCellX() const{return x;}
	int getCellY() const{return y;}
	cellType getCellType()const{return type;}
};

class Board {
	Cell **board;

public:
	int width;
	int height;
	Board(int width = 10, int height = 10);

	cellType getType(int i, int j);
	void setType(int, int, cellType);
	void debug_display() const;
	void placeFood();
	Cell getCell(int x, int y);
};

#endif //SNAKE_CELL_H