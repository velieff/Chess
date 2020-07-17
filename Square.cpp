#include<iostream>
#include"Square.h"
#include"Figure.h"


Square::Square()
{
	figure = NULL;
}

Square::~Square()
{
	makeEmpty();
}

void Square::set(Square* s)
{
	makeEmpty();
	figure = s->getFigure()->getCopy(s->getFigureColor());
}

void Square::print() const
{
	if (figure)
	{
		figure->print();
	}
	else
	{
		std::cout << " " << "\21" << " ";
	}
}

void Square::makeEmpty()
{
	if (figure)
	{
		delete figure;
		figure = NULL;
	}
}

Figure* Square::getFigure() const
{
	return figure;
}

void Square::putFigure(Figure* f)
{
	makeEmpty();
	figure = f;
}

Color Square::getFigureColor()const
{
	return figure ? figure->getColor() : NONE;
}
