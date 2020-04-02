#pragma once

#include <iostream>
#include <cmath>
#include <string>

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };

class Square
{
	
	Piece piece;
	Color color;
	int x, y;
public:
	void setSpace(Square*);
	void setEmpty();
	void setPieceAndColor(Piece, Color);
	Piece getPiece();
	Color getColor();
	void setX(int newX) { x = newX; }
	void setY(int newY) { y = newY; }
	int getX() { return x; }
	int getY() { return y; }
	Square();
};

class Board
{
	Square square[8][8];
	Color turn=WHITE;
	bool moveKing(Square* currentSquare, Square* newSquare);
	bool moveQueen(Square* currentSquare, Square* newSquare);
	bool moveBishop(Square* currentSquare, Square* newSquare);
	bool moveKnight(Square* currentSquare, Square* newSquare);
	bool moveRook(Square* currentSquare, Square* newSquare);
	bool movePawn(Square* currentSquare, Square* newSquare);
	bool makeMove(int currentX, int currentY, int newX, int newY);
	void printBoard();
public:
	Square* getSquare(int x, int y) {
		return &square[x][y];
	}
	void setSquare(Square * s, int x, int y){
		square[x][y]=*s;
	}
	bool doMove();
	
	void setBoard();
	bool playGame();
};

