#include "TFigure.h"

void TFigure::Move(int x, int y)
{
	this->x = x;
	this->y = y;
}
void TFigure::Resize(int width, int height)
{
	this->width = width;
	this->height = height;
}
void TFigure::Draw()
{
	cout << "Figure::Draw" << endl;
}

TFigure::TFigure()
{
	cout << "TFigure ������" << endl;
}
TFigure::TFigure(int x, int y, int width, int height)
{
	Move(x, y);
	Resize(width, height);
	cout << "TFigure ������" << endl;
}


TFigure::~TFigure()
{
	cout << "TFigure ������ " << endl;
}
