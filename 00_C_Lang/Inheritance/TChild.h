#pragma once
#include "TParent.h"
class TChild:public TParent
{
public:
	void Humanity(void);       //�߰��� ����Լ�
	void Character(void);         //������ ����Լ�
	void Appearance(void);       //Ȯ��� ����Լ�
public:
	TChild();
	 ~TChild();
};

