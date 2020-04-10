#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include "Figure.h"

enum Color { WHITE, BLACK, NONE };

const int boardSize = 8;

class Square
{
private:
	Figure* figure;
	Color color;
	int x, y;
public:
	Square();
	~Square();
	void copy(Square* s);
	void print();
	void setFigureAndColor(Figure* f, Color c);
	void setEmpty();
	Figure* getFigure();
	Color getColor();
	void setX(int newX);
	void setY(int newY);
	int getX();
	int getY();
	void destroy();
};

class Board
{
private:
	Square square[boardSize][boardSize];
	Color turn = WHITE;
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