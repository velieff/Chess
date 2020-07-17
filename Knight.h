#pragma once

#include<iostream>
#include"Figure.h"

class Knight : public Figure
{
public:
	Knight() {};
	Knight(const Knight& f) { color = f.color; };
	Knight(Color c) { color = c; };
	virtual void print() const { color == WHITE ? std::cout << " H " : std::cout << " h "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY) const
	{
		return ((abs(currentX - newX) == 2 && abs(currentY - newY) == 1) ||
			(abs(currentX - newX) == 1 && abs(currentY - newY) == 2));
	};
	virtual bool goesStraight() const { return false; };
	virtual bool goesDiagonally() const { return false; };
	virtual Figure* getCopy(Color c) const { return new Knight(c); };
	virtual bool isKing() const { return false; };
}; 
