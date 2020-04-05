#pragma once

#include<iostream>
#include<fstream>
#include"Figure.h"

class Pawn : public Figure
{
public:
	Pawn() {};
	virtual void print(bool isWhite) {isWhite ? std::cout << " P " : std::cout << " p "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY) 
	{
		if ((currentX + 1 == newX || currentX - 1 == newX || currentX == newX)
			&& newY == currentY + 1)
		{
			return true;
		}
		return false;
	};
	virtual bool isCleanWay(Board& board, Square* currentSquare, Square* newSquare) { return true; };
	virtual Figure* getCopy() const { return new Pawn(*this); };
	virtual bool isKing() { return false; };
};