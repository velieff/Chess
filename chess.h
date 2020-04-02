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
	void setSp(Square*);
	void setEmp();
	void setPC(Piece, Color);
	Piece getP();
	Color getC();
	void setX(int ex) { x = ex; }
	void setY(int why) { y = why; }
	int getX() { return x; }
	int getY() { return y; }
	Square();
};

class Board
{
	Square square[8][8];
	Color turn=WHITE;
	bool moveK(Square* thisKing, Square* thatSpace);
	bool moveQ(Square* thisQueen, Square* thatSpace);
	bool moveB(Square* thisBishop, Square* thatSpace);
	bool moveKN(Square* thisKnight, Square* thatSpace);
	bool moveR(Square* thisRook, Square* thatSpace);
	bool moveP(Square* thisPawn, Square* thatSpace);
	bool makeMove(int x1, int y1, int x2, int y2);
	void print();
public:
	Square* getSq(int x, int y) {
		return &square[x][y];
	}
	void setSq(Square * s, int x, int y){
		square[x][y]=*s;
	}
	bool doMove();
	
	void setBrd();
	bool playGame();
};

