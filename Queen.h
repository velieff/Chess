#pragma once

#include<iostream>
#include<fstream>
#include"Figure.h"

class Queen : public Figure
{
public:
	Queen() {};
	virtual void print(bool isWhite) { isWhite ? std::cout << " Q " : std::cout << " q "; };
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY)
	{
		if ((currentX == newX || currentY == newY) || (abs(currentX - newX) == abs(currentY - newY)))
		{
			return true;
		}
		return false;
	};
	virtual bool isCleanWay(Board& thisBoard, Square* currentSquare, Square* newSquare)
	{
		if (currentSquare->getX() == newSquare->getX())
		{
			int yIncrement = (newSquare->getY() - currentSquare->getY()) / (abs(newSquare->getY() - currentSquare->getY()));
			for (int i = currentSquare->getY() + yIncrement; i != newSquare->getY(); i += yIncrement)
			{
				if (thisBoard.getSquare(newSquare->getX(), i)->getColor() != NONE)
					return false;
			}
		}
		else
		{
			if (currentSquare->getY() == newSquare->getY())
			{
				int xIncrement = (newSquare->getX() - currentSquare->getX()) / (abs(newSquare->getX() - currentSquare->getX()));
				for (int i = currentSquare->getX() + xIncrement; i != newSquare->getX(); i += xIncrement)
				{
					if (thisBoard.getSquare(newSquare->getY(), i)->getColor() != NONE)
						return false;
				}
			}
		}

		if (abs(currentSquare->getX() - newSquare->getX()) == abs(currentSquare->getY() - newSquare->getY()))
		{
			int xIncrement = (newSquare->getX() - currentSquare->getX()) / (abs(newSquare->getX() - currentSquare->getX()));
			int yIncrement = (newSquare->getY() - currentSquare->getY()) / (abs(newSquare->getY() - currentSquare->getY()));

			for (int i = 1; i < abs(currentSquare->getX() - newSquare->getX()); i++)
			{
				if (thisBoard.getSquare((currentSquare->getX() + xIncrement * i), (currentSquare->getY() + yIncrement * i))->getColor() != NONE)
					return false;
			}
		}

		return true;
	};
	virtual Figure* getCopy() const { return new Queen(*this); };
	virtual bool isKing() { return false; };
};
