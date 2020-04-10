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
	color = NONE;
}

Square::~Square()
{
	destroy();
}

void Square::copy(Square* s)
{
	color = s->getColor();
	destroy();
	figure = s->getFigure()->getCopy();
}

void Square::print()
{
	if(figure && color != NONE) 
		figure->print(color == WHITE);
	else
		cout << " " << "\21" << " ";
}

void Square::setEmpty()
{
	color = NONE;
	destroy();
}

Figure* Square::getFigure()
{
	return figure;
}

Color Square::getColor()
{
	return color;
}

void Square::setFigureAndColor(Figure* f, Color c)
{
	destroy();
	figure = f;
	color = c;
}

void Square::setX(int newX)
{
	x = newX; 
}

void Square::setY(int newY)
{
	y = newY;
}

int Square::getX() 
{ 
	return x;
}

int Square::getY() 
{ 
	return y;
}

void Square::destroy()
{
	if (figure)
	{
		delete figure;
	}
}

Board::Board()
{
	for (int i = 0; i < boardSize / 2 + 1; i++)
	{
		Figure* f = NULL;
		switch (i)
		{
		case 0: f=new Rook(); break;
		case 1: f=new Knight(); break;
		case 2: f=new Bishop(); break;
		case 3: f=new Queen(); break;
		case 4: f=new King(); break;
		default: break;
		}
		square[i][0].setFigureAndColor(f, WHITE);
		square[i][7].setFigureAndColor(f->getCopy(), BLACK);
		square[i][1].setFigureAndColor(new Pawn(), WHITE);
		square[i][6].setFigureAndColor(new Pawn(), BLACK);

		if (i < 3)
		{
			square[boardSize - i - 1][0].setFigureAndColor(f->getCopy(), WHITE);
			square[boardSize - i - 1][7].setFigureAndColor(f->getCopy(), BLACK);
			square[boardSize - i - 1][1].setFigureAndColor(new Pawn(), WHITE);
			square[boardSize - i - 1][6].setFigureAndColor(new Pawn(), BLACK);
		}
	}

	for (int i = 2; i < boardSize - 2; i++)
	{
		for (int j = 0; j < boardSize; j++)
			square[j][i].setFigureAndColor(NULL, NONE);

	}
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			square[i][j].setX(i);
			square[i][j].setY(j);
		}
	}
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
		&& currentSquare->getFigure()->isCleanWay(*this, currentSquare, newSquare);
}

void Board::move(Square* currentSquare, Square* newSquare)
{
	newSquare->copy(currentSquare);
	currentSquare->setEmpty();
}