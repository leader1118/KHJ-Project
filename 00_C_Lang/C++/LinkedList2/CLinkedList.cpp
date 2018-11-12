#include "CLinkedList.h"

void CLinkedList::Add() 
{
	//첫번째 생성
	if (m_Head == NULL)
	{
		m_Head = new Node(iMAX++); // HEAD 동적할당
		m_Tail = m_Head; //Tail과 Head 연결
		m_Tail->m_pNext = NULL; //Tail의 Next가 NULL

		return;
	}
	// 두번쨰 생성
	m_Tail->m_pNext = new Node(iMAX++); //Tail의 next 동적할당
	m_Tail = m_Tail->m_pNext; //Tail을 next에 연결
	m_Tail->m_pNext = NULL; //Tail의 next가 NULL
}
void CLinkedList::Del(int aData)
{
	if (m_Head != NULL) // Head가 NULL이 아닐경우
	{
		if (m_Head->m_pNext == NULL) //Head의 next가 NULL일 경우
		{
			if (m_Head->iData == aData) //head의 iData가 aData와 같을 경우
			{
				delete m_Head; //Head를 삭제
			}return;
		}
		if (m_Head->m_pNext != NULL) //Head의 next가 NULL이 아닌경우
		{
			Node* pTemp; //빈 노드
			if (m_Head->iData == aData)//head의 iData가 aData와 같을 경우
			{
				pTemp = m_Head->m_pNext; //temp에 Head의 next를 저장
				delete m_Head; //헤더를 삭제
				m_Head = pTemp; //Head에 다시 저장
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
			Node* DelNode = pTemp->m_pNext; // 지울 노드의 next를 저장
			Node* DelNodeNext = DelNode->m_pNext; 
			delete DelNode;
			pTemp->m_pNext = DelNodeNext;
		}
	}
}
void CLinkedList::Print()
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
void CLinkedList::Find(int sData)
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

CLinkedList::CLinkedList()
{
	m_Head = 0;
	m_Tail = 0;
	iMAX = 0;
}


CLinkedList::~CLinkedList()
{
}
