#include "SServerObj.h"



SServerObj::SServerObj(void)
{
	InitializeCriticalSection(&m_cs); // �Ӱ迵�� �ʱ�ȭ �Լ�
}


SServerObj::~SServerObj(void)
{
	DeleteCriticalSection(&m_cs); // �Ӱ� ���� �Ҹ� �Լ�
}
