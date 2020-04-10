#pragma once

#include<iostream>
#include<fstream>
#include"Figure.h"

class Bishop : public Figure
{
public:
	Bishop() {};
	virtual void print(bool isWhite) { isWhite ? std::cout << " B " : std::cout << " b "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY)
	{
		if (abs(currentX - newX) == abs(currentY - newY))
		{
			return true;
		}
		return false;
	};
	virtual bool isCleanWay(Board& thisBoard, Square* currentSquare, Square* newSquare)
	{
		int xIncrement = (newSquare->getX() - currentSquare->getX()) / (abs(newSquare->getX() - currentSquare->getX()));
		int yIncrement = (newSquare->getY() - currentSquare->getY()) / (abs(newSquare->getY() - currentSquare->getY()));

		for (int i = 1; i < abs(currentSquare->getX() - newSquare->getX()); i++)
		{
			if (thisBoard.getSquare((currentSquare->getX() + xIncrement * i), (currentSquare->getY() + yIncrement * i))->getColor() != NONE)
				return false;
		}
		return true;
	};
	virtual Figure* getCopy() const { return new Bishop(*this); };
	virtual bool isKing() { return false; };
};
