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
	void getCopy(Square* s);
	void print();
	void putFigure(Figure* f);
	void makeEmpty();
	Figure* getFigure();
	Color getFigureColor();
};