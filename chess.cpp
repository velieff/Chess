#include "chess.h"


Square::Square()
{
	piece = EMPTY;
	color = NONE;
}

void Square::setSp(Square* space)
{
	color = space->getC();
	piece = space->getP();
}

void Square::setEmp()
{
	color = NONE;
	piece = EMPTY;
}

Piece Square::getP()
{
	return piece;
}

Color Square::getC()
{
	return color;
}

void Square::setPC(Piece p, Color c)
{
	piece = p;
	color = c;

}


void Board::print() {
	using namespace std;
	cout << "   y: 0  1  2  3  4  5  6  7 " << endl << "x:" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << " " << i << "   ";
		for (int j = 0; j < 8; j++)
		{
			Piece p = square[i][j].getP();
			Color c = square[i][j].getC();

			switch (p)
			{
			case KING: (c == WHITE) ? cout << " K " : cout << " k ";
				break;
			case QUEEN: (c == WHITE) ? cout << " Q " : cout << " q ";
				break;
			case BISHOP:(c == WHITE) ? cout << " B " : cout << " b ";
				break;
			case KNIGHT:(c == WHITE) ? cout << " H " : cout << " h ";
				break;
			case ROOK: (c == WHITE) ? cout << " R " : cout << " r ";
				break;
			case PAWN: (c == WHITE) ? cout << " P " : cout << " p ";
				break;
			case EMPTY: cout << " " << "\21" << " ";
				break;
			default: cout << "XXX";
				break;
			}

		}
		cout << endl;
	}

}

bool Board::doMove() {
	using namespace std;
	string move;
	int x1, x2, y1, y2;
	bool stop = false;
	while (!stop)
	{
		(turn == WHITE) ? cout << "White's turn" << endl : cout << "Black's turn" << endl;
		cout << "Type in your move as a single four character string. Use x-coordinates first in each pair." << endl;
		cin >> move;
		x1 = move[0] - 48;
		y1 = move[1] - 48;
		x2 = move[2] - 48;
		y2 = move[3] - 48;
		if (getSq(x1, y1)->getC() == turn)
		{


			if (makeMove(x1, y1, x2, y2) == false)
			{
				cout << "Invalid move, try again." << endl;
			}
			else
				stop = true;
		}
		else
			cout << "That's not your piece. Try again." << endl;
	}
	if (getSq(x2, y2)->getP() == KING)
		if (getSq(x1, y1)->getC() == WHITE)
		{
			cout << "WHITE WINS" << endl;
			return false;
		}
		else

		{
			cout << "BLACK WINS" << endl;
			return false;
		}


	if (turn == BLACK)
		turn = WHITE;
	else
		turn = BLACK;

	return true;

}

void Board::setBrd()
{
	square[0][0].setPC(ROOK, WHITE);
	square[1][0].setPC(KNIGHT, WHITE);
	square[2][0].setPC(BISHOP, WHITE);
	square[3][0].setPC(QUEEN, WHITE);
	square[4][0].setPC(KING, WHITE);
	square[5][0].setPC(BISHOP, WHITE);
	square[6][0].setPC(KNIGHT, WHITE);
	square[7][0].setPC(ROOK, WHITE);

	square[0][7].setPC(ROOK, BLACK);
	square[1][7].setPC(KNIGHT, BLACK);
	square[2][7].setPC(BISHOP, BLACK);
	square[3][7].setPC(QUEEN, BLACK);
	square[4][7].setPC(KING, BLACK);
	square[5][7].setPC(BISHOP, BLACK);
	square[6][7].setPC(KNIGHT, BLACK);
	square[7][7].setPC(ROOK, BLACK);

	for (int i = 0; i < 8; i++)
	{
		square[i][1].setPC(PAWN, WHITE);
		square[i][6].setPC(PAWN, BLACK);

	}
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[j][i].setPC(EMPTY, NONE);

	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			square[i][j].setX(i);
			square[i][j].setY(j);
		}

}

bool Board::playGame()
{
	system("cls");
	print();
	return doMove();

}

bool Board::moveK(Square* thisKing, Square* thatSpace) {
	if (abs(thatSpace->getX() - thisKing->getX()) == 1)
		if (abs(thatSpace->getY() - thisKing->getY()) == 1)
		{
			thatSpace->setSp(thisKing);
			thisKing->setEmp();
			return true;
		}
		else return false;
	else return false;
}
bool Board::moveQ(Square* thisQueen, Square* thatSpace) { 
	int queenX = thisQueen->getX();
	int queenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	std::cout << "this";
	int yIncrement;
	int xIncrement;

	bool invalid = false;
	if (queenX != thatX || queenY != thatY)
	{

		if (queenX == thatX)
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getC() != NONE)
					return false;

			}
		}
		else
			if (queenY == thatY)
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getC() != NONE)
						return false;
				}
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))
				{
					xIncrement = (thatX - queenX) / (abs(thatX - queenX));
					yIncrement = (thatY - queenY) / (abs(thatY - queenY));

					for (int i = 1; i < abs(queenX - thatX); i++)
					{
						std::cout << "It got here somehow";
						if (square[queenX + xIncrement*i][queenY + yIncrement*i].getC() != NONE)
							return false;

					}
				}
				else
					return false;
	}



	if (invalid == false)
	{
		thatSpace->setSp(thisQueen);
		thisQueen->setEmp();
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::moveB(Square* thisBishop, Square* thatSpace) {
	int bishopX = thisBishop->getX();
	int bishopY = thisBishop->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	if (abs(bishopX - thatX) == abs(bishopY - thatY))
	{
		int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
		int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

		for (int i = 1; i < abs(bishopX - thatX); i++)
		{
			std::cout << "It got here somehow";
			if (square[bishopX + xIncrement*i][bishopY + yIncrement*i].getC() != NONE)
				return false;

		}
	}
	else
		return false;

	if (invalid == false)
	{
		thatSpace->setSp(thisBishop);
		thisBishop->setEmp();
		return true;
	}
	else
	{
		return false;
	}
}
bool Board::moveKN(Square* thisKnight, Square* thatSpace) {
	int knightX = thisKnight->getX();
	int knightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
	{
		thatSpace->setSp(thisKnight);
		thisKnight->setEmp();
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::moveR(Square* thisRook, Square* thatSpace)
{
	int rookX = thisRook->getX();
	int rookY = thisRook->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	if (rookX != thatX || rookY != thatY)
	{

		if (rookX == thatX)
		{
			int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
			for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getC() != NONE)
					return false;

			}
		}
		else
			if (rookY == thatY)
			{

				int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
				for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getC() != NONE)
						return false;
				}
			}
			else
				return false;
	}
	if (invalid == false)
	{
		thatSpace->setSp(thisRook);
		thisRook->setEmp();
		return true;
	}
	else
	{
		std::cout << "That is an invalid move for rook";
		return false;
	}
}

bool Board::moveP(Square* thisPawn, Square* thatSpace) {
	using namespace std;
	bool invalid = false;
	int pawnX = thisPawn->getX();
	int pawnY = thisPawn->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();


	if (thisPawn->getC() == WHITE)
	{

		if (pawnX == thatX && thatY == pawnY + 1 && thatSpace->getC() == NONE)
		{
			thatSpace->setSp(thisPawn);
			thisPawn->setEmp();
			return true;
		}
		else
			if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY  && thatSpace->getC() == BLACK)
			{
				thatSpace->setSp(thisPawn);
				thisPawn->setEmp();
				return true;
			}
			else
				return false;
	}
	else
		if (thisPawn->getC() == BLACK)
		{
			if (pawnX == thatX && thatY == pawnY - 1 && thatSpace->getC() == NONE)
			{
				thatSpace->setSp(thisPawn);
				thisPawn->setEmp();
				return true;
			}
			else
				if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY  && thatSpace->getC() == WHITE)
				{
					thatSpace->setSp(thisPawn);
					thisPawn->setEmp();
					return true;
				}
				else
					return false;
		}
		else
			return false;
}
bool Board::makeMove(int x1, int y1, int x2, int y2) {

	using namespace std;
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		std::cout << "One of your inputs was out of bounds" << std::endl;
		return false;
	}
	Square* src = getSq(x1, y1);
	Square* dest = getSq(x2, y2);

	if (src->getC() == dest->getC() && dest->getC() != NONE)
	{
		std::cout << "Invalid move: cannot land on your own piece" << std::endl;
		return false;
	}

	switch (src->getP())
	{
	case KING: return moveK(src, dest);
		break;
	case QUEEN: return moveQ(src, dest);
		break;
	case BISHOP: return moveB(src, dest);
		break;
	case KNIGHT: return moveKN(src, dest);
		break;
	case ROOK: return moveR(src, dest);
		break;
	case PAWN: return moveP(src, dest);
		break;
	case EMPTY: std::cout << "You do not have a piece there" << std::endl;  return false;
		break;
	default: std::cerr << "Something went wrong in the switch statement in makeMove()" << std::endl;
		break;
	}
	return false;
}
