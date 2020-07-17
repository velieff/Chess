#pragma once

#include<iostream>
#include"Figure.h"

class Pawn : public Figure
{
public:
	Pawn() {};
	Pawn(const Pawn& f) { color = f.color; };
	Pawn(Color c) { color = c; };
	virtual void print() const { color == WHITE ? std::cout << " P " : std::cout << " p "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY) const
	{
		return ((currentX + 1 == newX || currentX - 1 == newX || currentX == newX)
			&& (newY == currentY + 1 || newY == currentY - 1));
	};
	virtual bool goesStraight() const { return true; };
	virtual bool goesDiagonally() const { return true; };
	virtual Figure* getCopy(Color c) const { return new Pawn(c); };
	virtual bool isKing()  const{ return false; };
};