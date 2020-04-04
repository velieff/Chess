#pragma once

#include <iostream>
#include <cmath>
#include <string>

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };

class Square
{
private:
	Piece piece;
	Color color;
	int x, y;
public:
	Square();
	void setSpace(Square*);
	void setEmpty();
	void setPieceAndColor(Piece, Color);
	Piece getPiece();
	Color getColor();
	void setX(int newX) { x = newX; }
	void setY(int newY) { y = newY; }
	int getX() { return x; }
	int getY() { return y; }
};

class Board
{
private:
	Square square[8][8];
	Color turn=WHITE;
	bool moveKing(Square* currentSquare, Square* newSquare);
	bool moveQueen(Square* currentSquare, Square* newSquare);
	bool moveBishop(Square* currentSquare, Square* newSquare);
	bool moveKnight(Square* currentSquare, Square* newSquare);
	bool moveRook(Square* currentSquare, Square* newSquare);
	bool movePawn(Square* currentSquare, Square* newSquare);
	bool moveFigure(int currentX, int currentY, int newX, int newY);
	void printBoard();
public:
	Board();
	Square* getSquare(int x, int y) { return &square[x][y]; }
	void setSquare(Square * s, int x, int y) { square[x][y] = *s; }
	bool makeMove();
	bool playGame();
};

