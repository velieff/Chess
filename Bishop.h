#pragma once

#include<iostream>
#include"Figure.h"

class Bishop : public Figure
{
public:
	Bishop() {};
	Bishop(const Bishop& f) { color = f.color; };
	Bishop(Color c) { color = c; };
	virtual void print() const { color == WHITE ? std::cout << " B " : std::cout << " b "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY) const
	{
		return (abs(currentX - newX) == abs(currentY - newY));
	};
	virtual bool goesStraight() const { return false; };
	virtual bool goesDiagonally() const { return true; };
	virtual Figure* getCopy(Color c) const { return new Bishop(c); };
	virtual bool isKing() const { return false; };
};
