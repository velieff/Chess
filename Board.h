#pragma once

#include<iostream>
#include<string>
#include"Square.h"
#include"Figure.h"

const int BOARD_SIZE = 8;

class Board
{
private:
	Square squares[BOARD_SIZE][BOARD_SIZE];
	bool isWhitesTurn;
	void move(Square* currentSquare, Square* newSquare);
	void printBoard() const;
	bool isValidMove(int currentX, int currentY, int newX, int newY);
	bool isPathFree(int currentX, int currentY, int newX, int newY);
	bool isFreeStraight(int currentX, int currentY, int newX, int newY);
	bool isFreeDiagonally(int currentX, int currentY, int newX, int newY);

public:
	Board();
	Square* getSquare(int x, int y) { return &squares[x][y]; }
	void setSquare(Square * s, int x, int y) { squares[x][y] = *s; }
	bool makeMove();
	bool playGame();
};