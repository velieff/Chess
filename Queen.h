#pragma once

#include<iostream>
#include<fstream>
#include"Figure.h"

class Queen : public Figure
{
public:
	Queen() {};
	Queen(const Queen& f) { color = f.color; };
	Queen(Color c) { color = c; };
	virtual void print() { color == WHITE ? std::cout << " Q " : std::cout << " q "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY)
	{
		if ((currentX == newX || currentY == newY) || (abs(currentX - newX) == abs(currentY - newY)))
		{
			return true;
		}
		return false;
	};
	virtual bool isCleanWay(Board thisBoard, int currentX, int currentY, int newX, int newY)
	{
		return isCleanStraight(thisBoard, currentX, currentY, newX, newY) ||
			   isCleanDiagonal(thisBoard, currentX, currentY, newX, newY);
	};
	virtual Figure* getCopy(Color c) const { return new Queen(c); };
	virtual bool isKing() { return false; };
};
