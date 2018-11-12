#include "TTemporary.h"
TTemporary::TTemporary(char* _name, int time, int pay) :TEmployee(_name)
{
	time = _time;
	pay = _pay;
}


TTemporary::GetPay()
{
	return time * pay;
}
