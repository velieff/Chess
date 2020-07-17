#include<iostream>
#include"Board.h"
#include"Square.h"
#include"Figure.h"
#include"Pawn.h"
#include"Rook.h"
#include"Knight.h"
#include"Bishop.h"
#include"Queen.h"
#include"King.h"

Board::Board()
{
	for (int i = 0; i < BOARD_SIZE / 2 + 1; i++)
	{
		Figure* f = NULL;
		switch (i)
		{
		case 0: f = new Rook(WHITE); break;
		case 1: f = new Knight(WHITE); break;
		case 2: f = new Bishop(WHITE); break;
		case 3: f = new Queen(WHITE); break;
		case 4: f = new King(WHITE); break;
		default: break;
		}
		squares[i][0].putFigure(f);
		squares[i][7].putFigure(f->getCopy(BLACK));
		squares[i][1].putFigure(new Pawn(WHITE));
		squares[i][6].putFigure(new Pawn(BLACK));

		if (i < 3)
		{
			squares[BOARD_SIZE - i - 1][0].putFigure(f->getCopy(WHITE));
			squares[BOARD_SIZE - i - 1][7].putFigure(f->getCopy(BLACK));
			squares[BOARD_SIZE - i - 1][1].putFigure(new Pawn(WHITE));
			squares[BOARD_SIZE - i - 1][6].putFigure(new Pawn(BLACK));
		}
	}
	isWhitesTurn = true;
}

void Board::printBoard()
{
	std::cout << "   y: 0  1  2  3  4  5  6  7\nx:\n";
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << " " << i << "   ";
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			squares[i][j].print();
		}
		std::cout << '\n';
	}

}

bool Board::playGame()
{
	system("cls");
	printBoard();
	return makeMove();
}

bool Board::makeMove()
{
	std::string command;
	int currentX, newX, currentY, newY;
	bool validMove = false;
	while (!validMove)
	{
		(isWhitesTurn) ? std::cout << "White's turn\n" : std::cout << "Black's turn\n";

		std::cout << "Type in your move as a single four character string. Use x-coordinates first in each pair.\n";
		std::cin >> command;
		currentX = command[0] - '0';
		currentY = command[1] - '0';
		newX = command[2] - '0';
		newY = command[3] - '0';
		if ((getSquare(currentX, currentY)->getFigureColor() == WHITE && isWhitesTurn) ||
			(getSquare(currentX, currentY)->getFigureColor() == BLACK && !isWhitesTurn))
		{
			if (isValidMove(currentX, currentY, newX, newY))
			{
				move(getSquare(currentX, currentY), getSquare(newX, newY));
				validMove = true;
			}
			else
			{
				std::cout << "Invalid move, try again.\n";
			}
		}
		else
		{
			std::cout << "That's not your piece. Try again.\n";
		}
	}
	if (getSquare(newX, newY)->getFigure()->isKing())
	{
		(getSquare(currentX, currentY)->getFigureColor() == WHITE) ? std::cout << "WHITE WINS\n" : std::cout << "BLACK WINS\n";
		return false;
	}

	isWhitesTurn = !isWhitesTurn;
	return true;

}

void Board::move(Square* currentSquare, Square* newSquare)
{
	newSquare->getCopy(currentSquare);
	currentSquare->makeEmpty();
}

bool Board::isValidMove(int currentX, int currentY, int newX, int newY)
{

	if (currentX < 0 || currentX>7 || currentY < 0 || currentY>7 || newX < 0 || newX>7 || newY < 0 || newY>8)
	{
		std::cout << "One of your inputs was out of bounds\n";
		return false;
	}
	Square* currentSquare = getSquare(currentX, currentY);
	Square* newSquare = getSquare(newX, newY);

	if (currentSquare->getFigureColor() == newSquare->getFigureColor() && newSquare->getFigureColor() != NONE)
	{
		std::cout << "Invalid move: cannot land on your own piece\n";
		return false;
	}

	return currentSquare->getFigure()->isValidMove(currentX, currentY, newX, newY) &&
		isCleanWay(currentX, currentY, newX, newY);
}

bool Board::isCleanWay(int currentX, int currentY, int newX, int newY)
{
	Figure * figure = getSquare(currentX, currentY)->getFigure();

	if (figure->goesStraight() && isCleanStraight(currentX, currentY, newX, newY))
	{
		return true;
	}

	if (figure->goesDiagonally() && isCleanDiagonally(currentX, currentY, newX, newY))
	{
		return true;
	}

	// THIS IS FOR THE KNIGHT BECAUSE IT CAN JUMP OVER OTHER FIGURES TO REACH ITS DESTINATION.
	if (!figure->goesStraight() && !figure->goesDiagonally())
	{
		return true;
	}

	return false;
}

bool Board::isCleanStraight(int currentX, int currentY, int newX, int newY)
{
	if (currentX == newX)
	{
		int increment = (newY - currentY) / (abs(newY - currentY));
		for (int i = currentY + increment; i != newY; i += increment)
		{
			if (getSquare(newX, i)->getFigureColor() != NONE)
			{
				return false;
			}
		}
		return true;
	}
	else if (currentY == newY)
	{
		int increment = (newX - currentX) / (abs(newX - currentX));
		for (int i = currentX + increment; i != newX; i += increment)
		{
			if (getSquare(newY, i)->getFigureColor() != NONE)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Board::isCleanDiagonally(int currentX, int currentY, int newX, int newY)
{
	if (newX - currentX == 0 || newY - currentY == 0)
	{
		return false;
	}

	int xIncrement = (newX - currentX) / (abs(newX - currentX));
	int yIncrement = (newY - currentY) / (abs(newY - currentY));

	for (int i = 1; i < abs(currentX - newX); i++)
	{
		if (getSquare((currentX + xIncrement * i), (currentY + yIncrement * i))->getFigureColor() != NONE)
		{
			return false;
		}
	}
	return true;
}