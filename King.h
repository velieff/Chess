#pragma once

#include<iostream>
#include<fstream>
#include"Figure.h"

class King : public Figure
{
public:
	King() {};
	virtual void print(bool isWhite) { isWhite ? std::cout << " K " : std::cout << " k "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY)
	{
		if ((abs(newX - currentX) == 1) && (abs(newY - currentY) == 1))
		{
			return true;
		}
		return false;
	};
	virtual bool isCleanWay(Board& board, Square* currentSquare, Square* newSquare) { return true; };
	virtual Figure* getCopy() const { return new King(*this); };
	virtual bool isKing() { return true; };
};
