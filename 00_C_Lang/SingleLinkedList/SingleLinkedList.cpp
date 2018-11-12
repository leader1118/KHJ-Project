#include "SingleLinkedList.h"
#include "Node.h"

void SingleLinkedList::AddNode()
{
	if (m_HeadNode == NULL)
	{
		return;
	}

	SNode* pNewNode = new SNode(++m_iCount);
	m_TailNode->m_pNextNode = pNewNode;
	m_TailNode = m_TailNode->m_pNextNode;
	m_TailNode->m_pNextNode = NULL;
}
void SingleLinkedList::AddNode(SNode* _pNewNode)
{
	if (m_HeadNode)
	{
		return;
	}
	_pNewNode->m_iData = ++m_iCount;
	m_TailNode->m_pNextNode = _pNewNode;
	m_TailNode = m_TailNode->m_pNextNode;
	m_TailNode->m_pNextNode = NULL;
}

void SingleLinkedList:: DelNode(SNode* _pPreNode)
{
	if (m_HeadNode == NULL)
	{
		return;
	}
	else if (_pPreNode == NULL || _pPreNode->m_pNextNode == NULL)
	{
		return;
	}

	SNode* pDelNode = _pPreNode->m_pNextNode;
	SNode* pNextNode = pDelNode->m_pNextNode;
	delete pDelNode;
	_pPreNode->m_pNextNode = pNextNode;
	m_iCount--;
}

void SingleLinkedList::DelNode(int _iData)
{
	if (m_HeadNode == NULL)
	{
		return;
	}

	SNode* pSearchPreNode = m_HeadNode;
	while (pSearchPreNode->m_pNextNode != NULL)
	{
		if (pSearchPreNode->m_pNextNode->m_iData == _iData)
		{
			DelNode(pSearchPreNode);
			return;
		}
		pSearchPreNode = pSearchPreNode->m_pNextNode;
	}
}

void SingleLinkedList::ShowAllData()
{
	for (SNode* pTemp = m_HeadNode;
		pTemp->m_pNextNode != NULL;
		pTemp = pTemp->m_pNextNode)
	{
		std::cout << pTemp->m_iData << std::endl;
	}
}

SingleLinkedList::SingleLinkedList()
{
	m_iCount = 0;
	SNode* FirstNode = new SNode(m_iCount);
	m_HeadNode = FirstNode;
	m_TailNode = m_HeadNode;
	m_TailNode->m_pNextNode = NULL;
}


SingleLinkedList::~SingleLinkedList()
{
	delete m_HeadNode;
}
