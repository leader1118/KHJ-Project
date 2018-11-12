#include "TRectangle.h"

void TRectangle::Draw()
{
	cout << "Draw Rectangle: ";
	cout << "(" << x << "," << y << "),";
	cout << width << "x" << height;
	cout << endl;
}
TRectangle::TRectangle()
{
	cout << "TRectangle ������" << endl;
}


TRectangle::TRectangle(int x,int y, int width, int height)
	:TFigure(x,y,width,height)
{
	cout << "TRectangle ������ " << endl;
}


TRectangle::~TRectangle()
{
	cout << "TRectangle ������" << endl;
}
