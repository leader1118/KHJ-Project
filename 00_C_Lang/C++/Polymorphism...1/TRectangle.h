#pragma once
#include "TFigure.h"
class TRectangle:public TFigure
{
public:
	void Draw();         //�������̵�
public:
	TRectangle();
	TRectangle(int x, int y,int width, int height);
	~TRectangle();
};

