#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include "Figure.h"

const int boardSize = 8;

class Square
{
private:
	Figure* figure;
public:
	Square();
	~Square();
	void copy(Square* s);
	void print();
	void setFigure(Figure* f);
	void setEmpty();
	Figure* getFigure();
	Color getColor();
};

class Board
{
private:
	Square square[boardSize][boardSize];
	Color turn;
	bool moveFigure(int currentX, int currentY, int newX, int newY);
	void move(Square* currentSquare, Square* newSquare);
	void printBoard();
public:
	Board();
	Square* getSquare(int x, int y) { return &square[x][y]; }
	void setSquare(Square * s, int x, int y) { square[x][y] = *s; }
	bool makeMove();
	bool playGame();
};