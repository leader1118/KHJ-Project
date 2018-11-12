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
	cout << "TTriangle 생성자" << endl;
}


TTriangle::~TTriangle()
{
	cout << "TTriangle 해제자" << endl;
}
