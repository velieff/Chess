#pragma once

#include<iostream>
#include"Figure.h"

class King : public Figure
{
public:
	King() {};
	King(const King& f) { color = f.color; };
	King(Color c) { color = c; };
	virtual void print() const { color == WHITE ? std::cout << " K " : std::cout << " k "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY) const
	{
		return ((abs(newX - currentX) <= 1) && (abs(newY - currentY) <= 1));
	};
	virtual bool goesStraight() const { return true; };
	virtual bool goesDiagonally() const { return true; };
	virtual Figure* getCopy(Color c) const { return new King(c); };
	virtual bool isKing() { return true; };
};
