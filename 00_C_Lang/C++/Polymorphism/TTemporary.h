#pragma once
#include "TEmployee.h"
class TTemporary : public TEmployee
{
private:
	int time; //���� �ð�
	int pay; //�ð��� �޿�
public:
	TTemporary(char* _name, int _time, int pay);
	int GetPay();
};

