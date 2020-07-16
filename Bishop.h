#pragma once

#include<iostream>
#include<fstream>
#include"Figure.h"

class Bishop : public Figure
{
public:
	Bishop() {};
	Bishop(const Bishop& f) { color = f.color; };
	Bishop(Color c) { color = c; };
	virtual void print() { color == WHITE ? std::cout << " B " : std::cout << " b "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY)
	{
		if (abs(currentX - newX) == abs(currentY - newY))
		{
			return true;
		}
		return false;
	};
	virtual bool isCleanWay(Board thisBoard, int currentX, int currentY, int newX, int newY)
	{
		return isCleanDiagonal(thisBoard, currentX, currentY, newX, newY);
	};
	virtual Figure* getCopy(Color c) const { return new Bishop(c); };
	virtual bool isKing() { return false; };
};
