#include "stdafx.h"
#include "TAccept.h"
#include "SSynchronize.h" // SLOCK으로 이름 ㄱ



void main()
{
	TAccept svr;
	svr.Set(10000);
	svr.CreateThread();
	while (1);
	
}