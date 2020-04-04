#include "chess.h"
using namespace std;

Square::Square()
{
	piece = EMPTY;
	color = NONE;
}

void Square::setSpace(Square* space)
{
	color = space->getColor();
	piece = space->getPiece();
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

Board::Board()
{
	int n = 7;
	for (int i = 0; i < 3; i++)
	{
		Piece p;
		switch (i)
		{
		case 0: p = ROOK; break;
		case 1: p = KNIGHT; break;
		case 2: p = BISHOP; break;
		default: cout << "X"; break;
		}
		square[i][0].setPieceAndColor(p, WHITE);
		square[n - i][0].setPieceAndColor(p, WHITE);
		square[i][7].setPieceAndColor(p, BLACK);
		square[n - i][7].setPieceAndColor(p, BLACK);

		square[i][1].setPieceAndColor(PAWN, WHITE);
		square[n - i][1].setPieceAndColor(PAWN, WHITE);
		square[i][6].setPieceAndColor(PAWN, BLACK);
		square[n - i][6].setPieceAndColor(PAWN, BLACK);
	}
	for (int i = 3; i < 5; i++)
	{
		Piece p;
		(i == 3) ? p = QUEEN : p = KING;
		square[i][0].setPieceAndColor(p, WHITE);
		square[i][7].setPieceAndColor(p, BLACK);
		square[i][1].setPieceAndColor(PAWN, WHITE);
		square[i][6].setPieceAndColor(PAWN, BLACK);
	}

	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[j][i].setPieceAndColor(EMPTY, NONE);

	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			square[i][j].setX(i);
			square[i][j].setY(j);
		}
	}
}

void Board::printBoard()
{
	cout << "   y: 0  1  2  3  4  5  6  7 " << endl << "x:" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << " " << i << "   ";
		for (int j = 0; j < 8; j++)
		{
			Piece p = square[i][j].getPiece();
			Color c = square[i][j].getColor();

			switch (p)
			{
			case KING: (c == WHITE) ? cout << " K " : cout << " k "; break;
			case QUEEN: (c == WHITE) ? cout << " Q " : cout << " q "; break;
			case BISHOP:(c == WHITE) ? cout << " B " : cout << " b "; break;
			case KNIGHT:(c == WHITE) ? cout << " H " : cout << " h "; break;
			case ROOK: (c == WHITE) ? cout << " R " : cout << " r "; break;
			case PAWN: (c == WHITE) ? cout << " P " : cout << " p "; break;
			case EMPTY: cout << " " << "\21" << " "; break;
			default: cout << "XXX"; break;
			}

		}
		cout << endl;
	}

}

bool Board::makeMove()
{
	string move;
	int currentX, newX, currentY, newY;
	bool stop = false;
	while (!stop)
	{
		(turn == WHITE) ? cout << "White's turn" << endl : cout << "Black's turn" << endl;

		cout << "Type in your move as a single four character string. Use x-coordinates first in each pair." << endl;
		cin >> move;
		currentX = move[0] - 48;
		currentY = move[1] - 48;
		newX = move[2] - 48;
		newY = move[3] - 48;
		if (getSquare(currentX, currentY)->getColor() == turn)
		{
			if (moveFigure(currentX, currentY, newX, newY) == false)
			{
				cout << "Invalid move, try again." << endl;
			}
			else
				stop = true;
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

bool Board::playGame()
{
	system("cls");
	printBoard();
	return makeMove();
}

bool Board::moveKing(Square* currentSquare, Square* newSquare)
{
	int currentX = currentSquare->getX(), currentY = currentSquare->getY(), newX = newSquare->getX(), newY = newSquare->getY();

	if ((abs(newX - currentX) == 1) &&
		(abs(newY - currentY) == 1))
	{
		newSquare->setSpace(currentSquare);
		currentSquare->setEmpty();
		return true;
	}
	return false;
}
bool Board::moveQueen(Square* currentSquare, Square* newSquare)
{
	int currentX = currentSquare->getX(), currentY = currentSquare->getY(),	newX = newSquare->getX(), newY = newSquare->getY();

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

	newSquare->setSpace(currentSquare);
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

	newSquare->setSpace(currentSquare);
	currentSquare->setEmpty();
	return true;
}
bool Board::moveKnight(Square* currentSquare, Square* newSquare)
{
	int currentX = currentSquare->getX(), currentY = currentSquare->getY(), newX = newSquare->getX(), newY = newSquare->getY();

	if ((abs(currentX - newX) == 2 && abs(currentY - newY) == 1) || (abs(currentX - newX) == 1 && abs(currentY - newY) == 2))
	{
		newSquare->setSpace(currentSquare);
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

	newSquare->setSpace(currentSquare);
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
			newSquare->setSpace(currentSquare);
			currentSquare->setEmpty();
			return true;
		}
		else
		{
			if ((currentX + 1 == newX || currentX - 1 == newX) && currentY + 1 == newY && newSquare->getColor() == BLACK)
			{
				newSquare->setSpace(currentSquare);
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
				newSquare->setSpace(currentSquare);
				currentSquare->setEmpty();
				return true;
			}
			else
				if ((currentX + 1 == newX || currentX - 1 == newX) && currentY - 1 == newY  && newSquare->getColor() == WHITE)
				{
					newSquare->setSpace(currentSquare);
					currentSquare->setEmpty();
					return true;
				}
				else
					return false;
		}
		else
			return false;
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
