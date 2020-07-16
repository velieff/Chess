#pragma once

#include<iostream>
#include<fstream>
#include"Figure.h"

class Knight : public Figure
{
public:
	Knight() {};
	Knight(const Knight& f) { color = f.color; };
	Knight(Color c) { color = c; };
	virtual void print() { color == WHITE ? std::cout << " H " : std::cout << " h "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY)
	{
		if ((abs(currentX - newX) == 2 && abs(currentY - newY) == 1) || (abs(currentX - newX) == 1 && abs(currentY - newY) == 2))
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	virtual bool isCleanWay(Board thisBoard, int currentX, int currentY, int newX, int newY) { return true; };
	virtual Figure* getCopy(Color c) const { return new Knight(c); };
	virtual bool isKing() { return false; };
}; 
