#include "TChild.h"

void TChild::Humanity(void)
{
	cout << "��ġ�� �ΰ���" << endl;
}
void TChild::Character(void)
{
	cout << "�� ���� ��ǰ " << endl;
}
void TChild::Appearance(void)
{
	TParent::Appearance(); //��� Ŭ�������� ������ ���
	cout << "��ĥ�� Ű" << endl; //�Ļ� Ŭ�������� Ȯ��� ���
}

//TChild::TChild()
//{
//	cout << "Child ������" << endl;
//}
TChild::TChild(void) : TParent(1000)
{
	cout << "Child ������" << endl;
}

TChild::~TChild()
{
	cout << "Child �Ҹ���" << endl;
}
