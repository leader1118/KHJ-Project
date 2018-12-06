#include "S_SvrObj.h"



S_SvrObj::S_SvrObj()
{
	InitializeCriticalSection(&m_Ct);
}


S_SvrObj::~S_SvrObj()
{
	DeleteCriticalSection(&m_Ct);
}
