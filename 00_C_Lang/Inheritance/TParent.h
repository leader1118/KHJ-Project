#pragma once
#include <iostream>
using namespace std;

class TParent
{
public:
	TParent(void);          //������
	~TParent(void);           //�Ҹ���
	TParent(int money);

	void Character(void);        //��ǰ ���
	void Appearance(void);       //�ܸ� ���
	void Wealth(void);           // ��� ���

private:
	int money;         // �� ����
};

