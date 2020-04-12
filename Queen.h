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
	virtual bool isCleanWay(Board& thisBoard, int currentX, int currentY, int newX, int newY)
	{
		if (currentX == newX)
		{
			int yIncrement = (newY - currentY) / (abs(newY - currentY));
			for (int i = currentY + yIncrement; i != newY; i += yIncrement)
			{
				if (thisBoard.getSquare(newX, i)->getColor() != NONE)
					return false;
			}
		}
		else
		{
			if (currentY == newY)
			{
				int xIncrement = (newX - currentX) / (abs(newX - currentX));
				for (int i = currentX + xIncrement; i != newX; i += xIncrement)
				{
					if (thisBoard.getSquare(newY, i)->getColor() != NONE)
						return false;
				}
			}
		}

		if (abs(currentX - newX) == abs(currentY - newY))
		{
			int xIncrement = (newX - currentX) / (abs(newX - currentX));
			int yIncrement = (newY - currentY) / (abs(newY - currentY));

			for (int i = 1; i < abs(currentX - newX); i++)
			{
				if (thisBoard.getSquare((currentX + xIncrement * i), (currentY + yIncrement * i))->getColor() != NONE)
					return false;
			}
		}

		return true;
	};
	virtual Figure* getCopy(Color c) const { return new Queen(c); };
	virtual bool isKing() { return false; };
};
