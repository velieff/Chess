#pragma once

#include<iostream>
#include"Figure.h"

class Rook : public Figure
{
public:
	Rook() {};
	Rook(const Rook& f) { color = f.color; };
	Rook(Color c) { color = c; };
	virtual void print() const { color == WHITE ? std::cout << " R " : std::cout << " r "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY) const
	{
		return (currentX == newX || currentY == newY);
	};
	virtual bool goesStraight() const { return true; };
	virtual bool goesDiagonally() const { return false; };
	virtual Figure* getCopy(Color c) const { return new Rook(c); };
	virtual bool isKing() const { return false; };
};
