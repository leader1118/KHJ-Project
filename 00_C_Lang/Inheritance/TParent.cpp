#include "TParent.h"



TParent::TParent(void)
{
	money = 100000000;
	cout << "Parent ������" << endl;
}
TParent::TParent(int money)
{
	this->money = money;
	cout << "Parent ������" << endl;
}

TParent::~TParent(void)
{
	cout << "Parent �Ҹ���" << endl;
}
void TParent::Character(void)
{
	cout << "������ ��ǰ" << endl;
}
void TParent::Appearance(void)
{
	cout << "�߻��� �ܸ�" << endl;
}
void TParent::Wealth(void)
{
	cout << "���:" << money << "��" << endl;
}
