#include "TQueue.h"
int TQueue::Get()
{
	if (m_iFront == m_iNear)
	{
		std::cout << "under flow" << std::endl;
	}
	int iValue = m_iQueueArray[m_iFront];
	m_iQueueArray[m_iFront]=-1;
	m_iFront = ++m_iFront % g_iMaxQueue;
	return iValue;
}
int TQueue::put(int iData)
{
	if ((m_iNear+1) % g_iMaxQueue==m_iFront)
	{
		std::cout << "over flow" << std::endl;
		return -1;
	}
	m_iQueueArray[m_iNear] = iData;
	m_iNear = ++m_iNear % g_iMaxQueue;
}
void TQueue::Show()
{
}


TQueue::TQueue() : m_iFront(0),m_iNear(0)
{
}


TQueue::~TQueue()
{
}
