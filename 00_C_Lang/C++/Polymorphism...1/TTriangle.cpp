#include "TTriangle.h"
void TTriangle::Draw()
{
	cout << "Draw TTriangle: ";
	cout << "(" << x << "," << y << "),";
	cout << width << "x" << height;
	cout << endl;
}


TTriangle::TTriangle()
{
	cout << "TTriangle ������" << endl;
}


TTriangle::~TTriangle()
{
	cout << "TTriangle ������" << endl;
}
