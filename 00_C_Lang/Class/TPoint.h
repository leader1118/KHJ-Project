#pragma once
#include<iostream>
#include<conio.h>
using namespace std;
class TPoint
{
public:
	int x;
	int y;
	void SetPosition(int _x, int _y);
	void Move(int _x, int _y);
	void Show(void);
public:
	TPoint();
	~TPoint();
};

