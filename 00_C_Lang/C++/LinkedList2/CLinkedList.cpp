#include "CLinkedList.h"

void CLinkedList::Add() 
{
	//ù��° ����
	if (m_Head == NULL)
	{
		m_Head = new Node(iMAX++); // HEAD �����Ҵ�
		m_Tail = m_Head; //Tail�� Head ����
		m_Tail->m_pNext = NULL; //Tail�� Next�� NULL

		return;
	}
	// �ι��� ����
	m_Tail->m_pNext = new Node(iMAX++); //Tail�� next �����Ҵ�
	m_Tail = m_Tail->m_pNext; //Tail�� next�� ����
	m_Tail->m_pNext = NULL; //Tail�� next�� NULL
}
void CLinkedList::Del(int aData)
{
	if (m_Head != NULL) // Head�� NULL�� �ƴҰ��
	{
		if (m_Head->m_pNext == NULL) //Head�� next�� NULL�� ���
		{
			if (m_Head->iData == aData) //head�� iData�� aData�� ���� ���
			{
				delete m_Head; //Head�� ����
			}return;
		}
		if (m_Head->m_pNext != NULL) //Head�� next�� NULL�� �ƴѰ��
		{
			Node* pTemp; //�� ���
			if (m_Head->iData == aData)//head�� iData�� aData�� ���� ���
			{
				pTemp = m_Head->m_pNext; //temp�� Head�� next�� ����
				delete m_Head; //����� ����
				m_Head = pTemp; //Head�� �ٽ� ����
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
			Node* DelNode = pTemp->m_pNext; // ���� ����� next�� ����
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
