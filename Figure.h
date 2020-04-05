#pragma once

#include<iostream>
#include<fstream>
#include"chess.h"

class Figure
{
public:
	Figure() {};
	virtual void print(bool isWhite) {};
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY) { return false; };
	virtual bool isCleanWay(Board& board, Square* currentSquare, Square* newSquare) { return false; };
	virtual Figure* getCopy() const { return NULL; };
	virtual bool isKing() { return false; };
};