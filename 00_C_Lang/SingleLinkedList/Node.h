#pragma once

#include <iostream>

struct SNode
{
	int m_iData;
	SNode* m_pNextNode;
	SNode() {}
	SNode(int _iData) { m_iData = _iData; m_pNextNode = NULL; }
};