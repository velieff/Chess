#pragma once

#include<iostream>
#include<fstream>
#include"Figure.h"

class Knight : public Figure
{
public:
	Knight() {};
	virtual void print(bool isWhite) { isWhite ? std::cout << " H " : std::cout << " h "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY)
	{
		if ((abs(currentX - newX) == 2 && abs(currentY - newY) == 1) || (abs(currentX - newX) == 1 && abs(currentY - newY) == 2))
		{
			return true;
		}
		else
			return false;
	};
	virtual bool isCleanWay(Board& board, Square* currentSquare, Square* newSquare) { return true; };
	virtual Figure* getCopy() const { return new Knight(*this); };
	virtual bool isKing() { return false; };
}; 
