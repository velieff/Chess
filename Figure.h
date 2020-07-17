#pragma once

#include<iostream>

enum Color { WHITE, BLACK, NONE };

class Figure
{
protected:
	Color color;

public:
	Figure() {};
	Figure(const Figure& f) { color = f.color; };
	Figure(Color c) { color = c; };
	Color getColor() const { return color; };
	void setColor(Color c) { color = c; };
	virtual void print() const {};
	virtual bool isValidMove(int currentX, int currentY, int newX, int newY) const { return false; };
	virtual bool goesStraight() const { return false; };
	virtual bool goesDiagonally() const { return false; };
	virtual Figure* getCopy(Color c) const { return NULL; };
	virtual bool isKing() const { return false; };

};