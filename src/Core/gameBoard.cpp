#include <vector>
#include <iostream>
#include <utility>
#include <ctime>
#include <stdlib.h>

#include "gameBoard.h"

int BOARDWIDTH ;
int BOARDHEIGHT ;

//Constructor, creating a board
Board::Board(int x, int y){
	width = x;
	height = y;
	board = new Cell*[y];
	for(int i =0;i<y;i++){
		board[i] = new Cell[x];
	}
	for(int i = 0;i<x;i++){
		for(int j=0;j<y;j++){
			board[i][j].setX(i);
			board[i][j].setY(j);
		}
	}
}

//Admin display for the board
void Board::debug_display()const{
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			if (board[i][j].getCellType() == cellType::EMPTY) {
				std::cout << " E ";
			}
			if (board[i][j].getCellType() == cellType::WALL) {
				std::cout << " W ";
			}
			if (board[i][j].getCellType() == cellType::SNAKE) {
				std::cout << " S ";
			}
			if (board[i][j].getCellType() == cellType::FOOD) {
				std::cout << " A ";
			}
		}
		std::cout << "\n";
	}
	std::cout<<"\n\n\n";
}

//Placing food on the board, only on field that is empty
void Board::placeFood(){
	std::vector<std::pair<int,int> > v;
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			if(board[i][j].getCellType() == cellType::EMPTY){
				v.push_back(std::make_pair(i,j));
			}
		}
	}
	srand(time(0));
	int s = v.size();
	int r = rand() % s;
	board[v[r].first][v[r].second].setType(cellType::FOOD);
}

//Setters and getters
void Board::setType(int i, int j, cellType t){
	board[i][j].setType(t);
}

cellType Board::getType(int i, int j){
	return board[i][j].getCellType();
}

Cell Board::getCell(int x, int y){
	return board[x][y];
}