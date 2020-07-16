#pragma once

#include<iostream>
#include<fstream>
#include"chess.h"

enum Color { WHITE, BLACK, NONE };

class Figure
{
protected:
	Color color;

public:
	Figure() {};
	Figure(const Figure& f) { color = f.color; };
	Figure(Color c) { color = c; };
	Color getColor() { return color; };
	void setColor(Color c) { color = c; };
	virtual void print() {};
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY) { return false; };
	virtual bool isCleanWay(Board thisBoard, int currentX, int currentY, int newX, int newY) { return false; };
	virtual Figure* getCopy(Color c) const { return NULL; };
	virtual bool isKing() { return false; };

};