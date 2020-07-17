#pragma once

#include <iostream>
#include <string>
#include "Figure.h"

class Square
{
private:
	Figure* figure;

public:
	Square();
	~Square();
	void set(Square* s);
	void print() const;
	void putFigure(Figure* f);
	void makeEmpty();
	Figure* getFigure() const;
	Color getFigureColor() const;
};