#pragma once

#include<iostream>
#include<fstream>
#include"Figure.h"

class Pawn : public Figure
{
public:
	Pawn() {};
	Pawn(const Pawn& f) { color = f.color; };
	Pawn(Color c) { color = c; };
	virtual void print() { color == WHITE ? std::cout << " P " : std::cout << " p "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY) 
	{
		if ((currentX + 1 == newX || currentX - 1 == newX || currentX == newX)
			&& newY == currentY + 1)
		{
			return true;
		}
		return false;
	};
	virtual bool isCleanWay(Board& board, int currentX, int currentY, int newX, int newY) { return true; };
	virtual Figure* getCopy(Color c) const { return new Pawn(c); };
	virtual bool isKing() { return false; };
};