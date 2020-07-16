#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include "Figure.h"

const int BOARD_SIZE = 8;

class Square
{
private:
	Figure* figure;

public:
	Square();
	~Square();
	void getCopy(Square* s);
	void print();
	void putFigure(Figure* f);
	void makeEmpty();
	Figure* getFigure();
	Color getColor();
};

class Board
{
private:
	Square squares[BOARD_SIZE][BOARD_SIZE];
	bool isWhitesTurn;
	bool isValidMove(int currentX, int currentY, int newX, int newY);
	void move(Square* currentSquare, Square* newSquare);
	void printBoard();

public:
	Board();
	Square* getSquare(int x, int y) { return &squares[x][y]; }
	void setSquare(Square * s, int x, int y) { squares[x][y] = *s; }
	bool makeMove();
	bool playGame();
};

bool isCleanStraight(Board thisBoard, int currentX, int currentY, int newX, int newY);
bool isCleanDiagonal(Board thisBoard, int currentX, int currentY, int newX, int newY);