#pragma once

#include<iostream>
#include<fstream>
#include"Figure.h"

class King : public Figure
{
public:
	King() {};
	King(const King& f) { color = f.color; };
	King(Color c) { color = c; };
	virtual void print() { color == WHITE ? std::cout << " K " : std::cout << " k "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY)
	{
		if ((abs(newX - currentX) == 1) && (abs(newY - currentY) == 1))
		{
			return true;
		}
		return false;
	};
	virtual bool isCleanWay(Board thisBoard, int currentX, int currentY, int newX, int newY) { return true; };
	virtual Figure* getCopy(Color c) const { return new King(c); };
	virtual bool isKing() { return true; };
};
