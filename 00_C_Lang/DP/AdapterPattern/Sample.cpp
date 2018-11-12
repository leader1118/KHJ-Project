// ���α׷��� �ۼ��ϴ� ���� ������ ����� ���� Ŭ������ ������ ��찡 �ִ�.
// ������ �� Ŭ������ �����ϰ� �; �����̶� �������� �ʰ� ����ϱ�� ����� ���̴�
//adapter ������ ���� Ŭ������ ������ �� �ֵ��� �߰����� �����ִ� ������ �Ѵ�.
//�� ȣȯ���� ���� ���� Ŭ������ �������̽��� ��ȯ�� ������ �� �ֵ��� ���ش�.
//adapter ������ ���� �� ���� ���·� ���ȴ�.1) Ŭ�����ƴ��� 2)������Ʈ �ƴ���

#include <iostream>
using namespace std;
	//#define CLASS_ADAPTER
#define OBJECT_ADAPTER

class Rectangle
{
public:
	Rectangle(int x1, int y1, int x2, int y2)
	{
		x1_ = x1;
		y1_ = y1;
		x2_ = x2;
		y2_ = y2;
	}
	void Draw() {}
private:
	int x1_, y1_, x2_, y2_;
};
class TextView
{
public:
	Rectangle GetExtent()
	{
		return Rectangle(x1_, y1_, x1_ + width_, y1_ + height_);
	}
private:
	int x1_, y1_;
	int width_, height_;
};
class Shape
{
public:
	virtual Rectangle BoundingBox() = 0;
};
class LineShape : public Shape
{
public:
	Rectangle BoundingBox()
	{
		return Rectangle(x1_, y1_, x2_, y2_);
	}
private:
	int x1_, y1_, x2_, y2_;
};
#if defined(CLASS_ADAPTER)
class Textshape : public Shape, private TextView
{
public:
	Rectangle BoundingBox()
	{
		return GetExtent();
	}
};
void DisplayBoundingBox(Shape* pSelectedShape)
{
	(pSelectedShape->BoundingBox()).Draw();
}
#elif defined(OBJECT_ADAPTER)
class LineShape :public Shape
{
public:
	Rectangle BoundingBox()
	{
		return Rectangle(x1_, y1_, x2_, y2_);
	}
private:
	int x1_, y1_, x2_, y2_;
};
class TextShape : public Shape
{
public:
	TextShape()
	{
		pText_ = new TextView;
	}
	Rectangle BoundingBox()
	{
		return pText_->GetExtent();
	}
private:
	TextView * pText_;
};
void DisplayBoundingBox(Shape* pSelectedShape)
{
	(pSelectedShape->BoundingBox()).Draw();
}
#else
void DisplayBoundingBox(Shape* pSelectedShape, TextView* pSelectedText)
{
	if (pSelectedText != 0)
	{
		(pSelectedText->GetExtent()).Draw();
	}
	else if (pSelectedShape != 0)
	{
		(pSelectedShape->BoundingBox()).Draw();
	}
	else
	{ }

}
#endif


void main()
{
#if defined(CLASS_ADPTER)||defined(OBJECT_ADAPTER)
	TextShape text;
	DisplayBoundingBox(&text);
#else
	TextView text;
	DisplayBoundingBox(0, &text);
#endif
}