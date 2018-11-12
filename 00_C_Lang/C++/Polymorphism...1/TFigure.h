#pragma once
#include <iostream>
using namespace std;

class TFigure
{
public:
	void Move(int x, int y);              //도형 이동
	void Resize(int width, int height);    // 도형 크기
	virtual void Draw();
protected:
	int x;        //중심의 x좌표
	int y;       //중심의 y좌표
	int width;     //가로길이
	int height;  //세로 길이
public:
	TFigure();
	TFigure(int x, int y, int width , int height);
	~TFigure();
};

