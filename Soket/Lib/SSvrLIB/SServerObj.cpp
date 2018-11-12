#include "SServerObj.h"



SServerObj::SServerObj(void)
{
	InitializeCriticalSection(&m_cs); // 임계영역 초기화 함수
}


SServerObj::~SServerObj(void)
{
	DeleteCriticalSection(&m_cs); // 임계 영역 소멸 함수
}
