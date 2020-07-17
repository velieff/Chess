#pragma once

#include<iostream>
#include"Figure.h"

class Queen : public Figure
{
public:
	Queen() {};
	Queen(const Queen& f) { color = f.color; };
	Queen(Color c) { color = c; };
	virtual void print() const { color == WHITE ? std::cout << " Q " : std::cout << " q "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY) const
	{
		return ((currentX == newX || currentY == newY) || (abs(currentX - newX) == abs(currentY - newY)));
	};
	virtual bool goesStraight() const { return true; };
	virtual bool goesDiagonally() const { return true; };
	virtual Figure* getCopy(Color c) const { return new Queen(c); };
	virtual bool isKing() const { return false; };
};
