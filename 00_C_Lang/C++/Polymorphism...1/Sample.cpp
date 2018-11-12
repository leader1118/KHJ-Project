#include "TEllipse.h"
#include "TTriangle.h"
#include "TRectangle.h"

int main(void)
{
	//TEllipse ellipse (30,20,50,20);
	//TTriangle triangle(10,10,20,30);
	//Trectangle rectangle(20,30,10,20);

	//ellipse.Draw();    //Ÿ�� �׸���
	//triangle.Draw();   //�ﰢ�� �׸���
	//rectangle.Draw();  //�簢�� �׸���

	const int FIGURES = 3;

	TFigure *figures[FIGURES] =
	{
		new TTriangle(10,10,20,30),
		new TTriangle(20,30,10,20),
		new TEllipse(30,20,50,20),
	};
	for (int i = 0; i < FIGURES; i++)
		figures[i]->Draw(); //����� ��� ���� �׸���

	for (int i = 0; i < FIGURES; i++)
		delete figures[i];

	return 0;
}