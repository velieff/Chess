#include<iostream>
#include "chess.h"
#include"Figure.h"
#include"Pawn.h"
#include"Rook.h"
#include"Knight.h"
#include"Bishop.h"
#include"Queen.h"
#include"King.h"
using namespace std;

Square::Square()
{
	figure = NULL;
}

Square::~Square()
{
	setEmpty();
}

void Square::copy(Square* s)
{
	setEmpty();
	figure = s->getFigure()->getCopy(s->getColor());
}

void Square::print()
{
	if(figure) 
		figure->print();
	else
		cout << " " << "\21" << " ";
}

void Square::setEmpty()
{
	if (figure)
	{
		delete figure;
		figure = NULL;
	}
}

Figure* Square::getFigure()
{
	return figure;
}

void Square::setFigure(Figure* f)
{
	setEmpty();
	figure = f;
}

Color Square::getColor()
{
	return figure ? figure->getColor() : NONE;
}

Board::Board()
{
	for (int i = 0; i < boardSize / 2 + 1; i++)
	{
		Figure* f = NULL;
		switch (i)
		{
		case 0: f=new Rook(WHITE); break;
		case 1: f=new Knight(WHITE); break;
		case 2: f=new Bishop(WHITE); break;
		case 3: f=new Queen(WHITE); break;
		case 4: f=new King(WHITE); break;
		default: break;
		}
		square[i][0].setFigure(f);
		square[i][7].setFigure(f->getCopy(BLACK));
		square[i][1].setFigure(new Pawn(WHITE));
		square[i][6].setFigure(new Pawn(BLACK));

		if (i < 3)
		{
			square[boardSize - i - 1][0].setFigure(f->getCopy(WHITE));
			square[boardSize - i - 1][7].setFigure(f->getCopy(BLACK));
			square[boardSize - i - 1][1].setFigure(new Pawn(WHITE));
			square[boardSize - i - 1][6].setFigure(new Pawn(BLACK));
		}
	}
	turn = WHITE;
}

void Board::printBoard()
{
	cout << "   y: 0  1  2  3  4  5  6  7 " << endl << "x:" << endl;
	for (int i = 0; i < boardSize; i++)
	{
		cout << " " << i << "   ";
		for (int j = 0; j < boardSize; j++)
		{
			square[i][j].print();
		}
		cout << endl;
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
	string command;
	int currentX, newX, currentY, newY;
	bool validMove = false;
	while (!validMove)
	{
		(turn == WHITE) ? cout << "White's turn" << endl : cout << "Black's turn" << endl;

		cout << "Type in your move as a single four character string. Use x-coordinates first in each pair." << endl;
		cin >> command;
		currentX = command[0] - 48;
		currentY = command[1] - 48;
		newX = command[2] - 48;
		newY = command[3] - 48;
		if (getSquare(currentX, currentY)->getColor() == turn)
		{
			if (moveFigure(currentX, currentY, newX, newY) == false)
			{
				cout << "Invalid move, try again." << endl;
			}
			else
			{
				move(getSquare(currentX, currentY), getSquare(newX, newY));
				validMove = true;
			}
		}
		else
			cout << "That's not your piece. Try again." << endl;
	}
	if (getSquare(newX, newY)->getFigure()->isKing())
	{
		(getSquare(currentX, currentY)->getColor() == WHITE) ? cout << "WHITE WINS\n" : cout << "BLACK WINS\n";
		return false;
	}
	
	(turn == BLACK) ? turn = WHITE : turn = BLACK;
	return true;

}

bool Board::moveFigure(int currentX, int currentY, int newX, int newY)
{

	if (currentX < 0 || currentX>7 || currentY < 0 || currentY>7 || newX < 0 || newX>7 || newY < 0 || newY>8)
	{
		cout << "One of your inputs was out of bounds" << endl;
		return false;
	}
	Square* currentSquare = getSquare(currentX, currentY);
	Square* newSquare = getSquare(newX, newY);

	if (currentSquare->getColor() == newSquare->getColor() && newSquare->getColor() != NONE)
	{
		cout << "Invalid move: cannot land on your own piece" << endl;
		return false;
	}

	return currentSquare->getFigure()->isValidMove(currentX, currentY, newX, newY)
		&& currentSquare->getFigure()->isCleanWay(*this, currentX, currentY, newX, newY);
}

void Board::move(Square* currentSquare, Square* newSquare)
{
	newSquare->copy(currentSquare);
	currentSquare->setEmpty();
}