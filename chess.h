#pragma once

#include <iostream>
#include <cmath>
#include <string>

enum Piece { ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN, EMPTY};
enum Color { WHITE, BLACK, NONE };

const int boardSize = 8;

class Square
{
private:
	Piece piece;
	Color color;
	int x, y;
public:
	Square();
	void copy(Square* s);
	void print();
	void setPieceAndColor(Piece p, Color c);
	void setEmpty();
	Piece getPiece();
	Color getColor();
	void setX(int newX);
	void setY(int newY);
	int getX();
	int getY();
};

class Board
{
private:
	Square square[boardSize][boardSize];
	Color turn = WHITE;
	bool moveFigure(int currentX, int currentY, int newX, int newY);
	bool moveKing(Square* currentSquare, Square* newSquare);
	bool moveQueen(Square* currentSquare, Square* newSquare);
	bool moveBishop(Square* currentSquare, Square* newSquare);
	bool moveKnight(Square* currentSquare, Square* newSquare);
	bool moveRook(Square* currentSquare, Square* newSquare);
	bool movePawn(Square* currentSquare, Square* newSquare);
	void printBoard();
public:
	Board();
	Square* getSquare(int x, int y) { return &square[x][y]; }
	void setSquare(Square * s, int x, int y) { square[x][y] = *s; }
	bool makeMove();
	bool playGame();
};
