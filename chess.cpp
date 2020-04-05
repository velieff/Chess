#include "chess.h"
using namespace std;

Square::Square()
{
	piece = EMPTY;
	color = NONE;
}

void Square::copy(Square* s)
{
	color = s->getColor();
	piece = s->getPiece();
}

void Square::print()
{
	switch (piece)
	{
	case KING: (color == WHITE) ? cout << " K " : cout << " k "; break;
	case QUEEN: (color == WHITE) ? cout << " Q " : cout << " q "; break;
	case BISHOP:(color == WHITE) ? cout << " B " : cout << " b "; break;
	case KNIGHT:(color == WHITE) ? cout << " H " : cout << " h "; break;
	case ROOK: (color == WHITE) ? cout << " R " : cout << " r "; break;
	case PAWN: (color == WHITE) ? cout << " P " : cout << " p "; break;
	case EMPTY: cout << " " << "\21" << " "; break;
	default: cout << "XXX"; break;
	}
}

void Square::setEmpty()
{
	color = NONE;
	piece = EMPTY;
}

Piece Square::getPiece()
{
	return piece;
}

Color Square::getColor()
{
	return color;
}

void Square::setPieceAndColor(Piece p, Color c)
{
	piece = p;
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

Board::Board()
{
	for (int i = 0; i < boardSize / 2 + 1; i++)
	{
		square[i][0].setPieceAndColor((Piece)i, WHITE);
		square[i][7].setPieceAndColor((Piece)i, BLACK);
		square[i][1].setPieceAndColor(PAWN, WHITE);
		square[i][6].setPieceAndColor(PAWN, BLACK);

		if (i < 3)
		{
			square[boardSize - i - 1][0].setPieceAndColor((Piece)i, WHITE);
			square[boardSize - i - 1][7].setPieceAndColor((Piece)i, BLACK);
			square[boardSize - i - 1][1].setPieceAndColor(PAWN, WHITE);
			square[boardSize - i - 1][6].setPieceAndColor(PAWN, BLACK);
		}
	}

	for (int i = 2; i < boardSize - 2; i++)
	{
		for (int j = 0; j < boardSize; j++)
			square[j][i].setPieceAndColor(EMPTY, NONE);

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
				validMove = true;
			}
		}
		else
			cout << "That's not your piece. Try again." << endl;
	}
	if (getSquare(newX, newY)->getPiece() == KING)
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

	switch (currentSquare->getPiece())
	{
	case KING: return moveKing(currentSquare, newSquare); break;
	case QUEEN: return moveQueen(currentSquare, newSquare); break;
	case BISHOP: return moveBishop(currentSquare, newSquare); break;
	case KNIGHT: return moveKnight(currentSquare, newSquare); break;
	case ROOK: return moveRook(currentSquare, newSquare); break;
	case PAWN: return movePawn(currentSquare, newSquare); break;
	case EMPTY: cout << "You do not have a piece there" << endl;  return false; break;
	default: cout << "Something went wrong in the switch statement in moveFigure()" << endl; return false; break;
	}
}

bool Board::moveKing(Square* currentSquare, Square* newSquare)
{
	int currentX = currentSquare->getX(), currentY = currentSquare->getY(), newX = newSquare->getX(), newY = newSquare->getY();

	if ((abs(newX - currentX) == 1) &&
		(abs(newY - currentY) == 1))
	{
		newSquare->copy(currentSquare);
		currentSquare->setEmpty();
		return true;
	}
	return false;
}
bool Board::moveQueen(Square* currentSquare, Square* newSquare)
{
	int currentX = currentSquare->getX(), currentY = currentSquare->getY(), newX = newSquare->getX(), newY = newSquare->getY();

	int yIncrement;
	int xIncrement;

	if (currentX != newX || currentY != newY)
	{

		if (currentX == newX)
		{
			yIncrement = (newY - currentY) / (abs(newY - currentY));
			for (int i = currentY + yIncrement; i != newY; i += yIncrement)
			{
				if (square[newX][i].getColor() != NONE)
					return false;
			}
		}
		else
		{
			if (currentY == newY)
			{

				xIncrement = (newX - currentX) / (abs(newX - currentX));
				for (int i = currentX + xIncrement; i != newX; i += xIncrement)
				{
					if (square[i][newY].getColor() != NONE)
						return false;
				}
			}
			else
			{
				if (abs(currentX - newX) == abs(currentY - newY))
				{
					xIncrement = (newX - currentX) / (abs(newX - currentX));
					yIncrement = (newY - currentY) / (abs(newY - currentY));

					for (int i = 1; i < abs(currentX - newX); i++)
					{
						cout << "It got here somehow";
						if (square[currentX + xIncrement * i][currentY + yIncrement * i].getColor() != NONE)
							return false;
					}
				}
				else
					return false;
			}
		}
	}

	newSquare->copy(currentSquare);
	currentSquare->setEmpty();
	return true;
}

bool Board::moveBishop(Square* currentSquare, Square* newSquare)
{
	int currentX = currentSquare->getX(), currentY = currentSquare->getY(), newX = newSquare->getX(), newY = newSquare->getY();

	if (abs(currentX - newX) == abs(currentY - newY))
	{
		int xIncrement = (newX - currentX) / (abs(newX - currentX));
		int yIncrement = (newY - currentY) / (abs(newY - currentY));

		for (int i = 1; i < abs(currentX - newX); i++)
		{
			cout << "It got here somehow";
			if (square[currentX + xIncrement * i][currentY + yIncrement * i].getColor() != NONE)
				return false;
		}
	}
	else
		return false;

	newSquare->copy(currentSquare);
	currentSquare->setEmpty();
	return true;
}
bool Board::moveKnight(Square* currentSquare, Square* newSquare)
{
	int currentX = currentSquare->getX(), currentY = currentSquare->getY(), newX = newSquare->getX(), newY = newSquare->getY();

	if ((abs(currentX - newX) == 2 && abs(currentY - newY) == 1) || (abs(currentX - newX) == 1 && abs(currentY - newY) == 2))
	{
		newSquare->copy(currentSquare);
		currentSquare->setEmpty();
		return true;
	}
	else
		return false;
}

bool Board::moveRook(Square* currentSquare, Square* newSquare)
{
	int currentX = currentSquare->getX(), currentY = currentSquare->getY(), newX = newSquare->getX(), newY = newSquare->getY();

	if (currentX != newX || currentY != newY)
	{

		if (currentX == newX)
		{
			int yIncrement = (newY - currentY) / (abs(newY - currentY));
			for (int i = currentY + yIncrement; i != newY; i += yIncrement)
			{
				if (square[newX][i].getColor() != NONE)
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
					if (square[i][newY].getColor() != NONE)
						return false;
				}
			}
			else
				return false;
		}
	}

	newSquare->copy(currentSquare);
	currentSquare->setEmpty();
	return true;
}

bool Board::movePawn(Square* currentSquare, Square* newSquare)
{
	int currentX = currentSquare->getX(), currentY = currentSquare->getY(), newX = newSquare->getX(), newY = newSquare->getY();

	if (currentSquare->getColor() == WHITE)
	{

		if (currentX == newX && newY == currentY + 1 && newSquare->getColor() == NONE)
		{
			newSquare->copy(currentSquare);
			currentSquare->setEmpty();
			return true;
		}
		else
		{
			if ((currentX + 1 == newX || currentX - 1 == newX) && currentY + 1 == newY && newSquare->getColor() == BLACK)
			{
				newSquare->copy(currentSquare);
				currentSquare->setEmpty();
				return true;
			}
			else
				return false;
		}
	}
	else
		if (currentSquare->getColor() == BLACK)
		{
			if (currentX == newX && newY == currentY - 1 && newSquare->getColor() == NONE)
			{
				newSquare->copy(currentSquare);
				currentSquare->setEmpty();
				return true;
			}
			else
				if ((currentX + 1 == newX || currentX - 1 == newX) && currentY - 1 == newY && newSquare->getColor() == WHITE)
				{
					newSquare->copy(currentSquare);
					currentSquare->setEmpty();
					return true;
				}
				else
					return false;
		}
		else
			return false;
}
