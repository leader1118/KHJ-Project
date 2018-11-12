#include "LinkedListSing.h"

void LinkedListSing::Add()
{
	//첫번째 생성
	if (m_Head == NULL)
	{
		m_Head = new Node(i_MAX++); // Head 동적할당
		m_Tail = m_Head; // Tail과 Head 연결
		m_Tail->m_pNext = NULL; //Tail의 Next가 NULL

		return; 
	}
	//두번째 생성
	m_Tail->m_pNext = new Node(i_MAX++); //Tail의 Next 동적할당
	m_Tail = m_Tail->m_pNext; 
	m_Tail->m_pNext = NULL; //Tail의 next가 NULL 
}
void LinkedListSing::Del(int aData)
{
	if (m_Head != NULL)
	{
		if (m_Head->m_pNext == NULL)
		{
			if (m_Head->iData == aData)
			{
				delete m_Head;
			}return;
		}

		if (m_Head->m_pNext != NULL)
		{
			Node* pTemp;
			if (m_Head->iData == aData)
			{
				pTemp = m_Head->m_pNext;
				delete m_Head;
				m_Head = pTemp;
			}
			for (pTemp = m_Head;
				pTemp->m_pNext != NULL;
				pTemp = pTemp->m_pNext)
			{
				if (pTemp->m_pNext->iData == aData)
				{
					break;
				}
			}
			Node* DelNode = pTemp->m_pNext;
			Node* DelNodeNext = DelNode->m_pNext;
			delete DelNode;
			pTemp->m_pNext = DelNodeNext;

		}
	}
}

void LinkedListSing::print()
{
	Node* pTemp;
	for (pTemp = m_Head;
		pTemp->m_pNext != NULL;
		pTemp = pTemp->m_pNext)
	{
		cout << pTemp->iData << endl;
	}
	cout << pTemp->iData << endl;
}
void LinkedListSing::Find(int sData)
{
	Node* pTemp;
	for (pTemp = m_Head;
		pTemp->m_pNext != NULL;
		pTemp = pTemp->m_pNext)
	{
		if (pTemp->m_pNext->iData == sData)
		{
			break;
		}
	}
}


LinkedListSing::LinkedListSing()
{
	m_Head = 0;
	m_Tail = 0;
	i_MAX = 0;
}


LinkedListSing::~LinkedListSing()
{
}
