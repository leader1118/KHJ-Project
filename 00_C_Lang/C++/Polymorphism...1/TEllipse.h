#pragma once
#include "TFigure.h"
class TEllipse: public TFigure
{
public:
	void Draw(); // �������̵�
public:
	TEllipse();
	TEllipse(int x,int y,int width,int height);
	~TEllipse();
};

