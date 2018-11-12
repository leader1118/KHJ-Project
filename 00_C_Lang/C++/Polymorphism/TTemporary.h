#pragma once
#include "TEmployee.h"
class TTemporary : public TEmployee
{
private:
	int time; //일한 시간
	int pay; //시간당 급여
public:
	TTemporary(char* _name, int _time, int pay);
	int GetPay();
};

