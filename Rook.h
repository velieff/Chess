#pragma once

#include<iostream>
#include<fstream>
#include"Figure.h"

class Rook : public Figure
{
public:
	Rook() {};
	Rook(const Rook& f) { color = f.color; };
	Rook(Color c) { color = c; };
	virtual void print() { color == WHITE ? std::cout << " R " : std::cout << " r "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY)
	{
		if (currentX == newX || currentY == newY)
		{
			return true;
		}
		return false;
	};
	virtual bool isCleanWay(Board thisBoard, int currentX, int currentY, int newX, int newY)
	{ 
		return isCleanStraight(thisBoard, currentX, currentY, newX, newY);
	};
	virtual Figure* getCopy(Color c) const { return new Rook(c); };
	virtual bool isKing() { return false; };
};
