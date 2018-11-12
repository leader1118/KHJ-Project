#pragma once

struct SNode;
class SingleLinkedList
{
public:
	SNode*  m_HeadNode;
	SNode*  m_TailNode;
	int     m_iCount;
public:
	void      AddNode();
	void      AddNode(SNode* _pNewNode);
	void      DelNode(int _iData);
	void      DelNode(SNode* _DelNode);
	void      ShowAllData();

public:
	SingleLinkedList();
	virtual ~SingleLinkedList();
};

