#pragma once
#include <iostream>

using namespace std;

struct TNode
{
	int          m_iKey;
	TNode*       m_pParent;
	char         m_cColor;
	TNode*       m_pLeft;
	TNode*       m_pRight;
};

class RBtree
{
	TNode * m_pRootNode;
	TNode * q;

public:
	RBtree()
	{
		q = NULL;
		m_pRootNode = NULL;
	}

	void insert(int iValue);
	void insertfix(TNode *);
	void leftrotate(TNode *);
	void rightrotate(TNode *);
	void del();
	TNode* successor(TNode *);
	void delfix(TNode *);
	void disp();
	void display(TNode *);
	void search();
};
void RBtree::insert(int iValue)
{
	TNode* p, *q;
	TNode* pNewNode = new TNode;
	pNewNode->m_iKey = iValue;
	pNewNode->m_pLeft = NULL;
	pNewNode->m_pRight = NULL;
	pNewNode->m_cColor = 'r';
	p = m_pRootNode;
	q = NULL;

	if (m_pRootNode == NULL)
	{
		m_pRootNode = pNewNode;
		pNewNode->m_pParent = NULL;
	}
	else
	{
		while (p != NULL)
		{
			q = p;
			if (p->m_iKey < pNewNode->m_iKey)
				p = p->m_pRight;
			else
				p = p->m_pLeft;
		}
		pNewNode->m_pParent = q;
		if (q->m_iKey < pNewNode->m_iKey)
			q = p->m_pRight;
		else
			p = p->m_pLeft=pNewNode;
	}
	insertfix(pNewNode);
}
void RBtree::insertfix(TNode* t)
{
	TNode *u;
	if (m_pRootNode == t)
	{
		t->m_cColor='b';
		return;
	}
	while (t->m_pParent != NULL && t->m_pParent->m_cColor == 'r')
	{
		TNode *g = t->m_pParent->m_pParent;
		if (g->m_pLeft == t->m_pParent)
		{
			if (g->m_pRight != NULL)
			{
				u = g->m_pRight;
				if (u->m_cColor == 'r')
				{
					t->m_pParent->m_cColor = 'b';
					u->m_cColor = 'b';
					g->m_cColor = 'r';
					t = g;
				}
			}
			else
			{
				if (t->m_pParent->m_pRight == t)
				{
					t = t->m_pParent;
					leftrotate(t);
				}
				t->m_pParent->m_cColor = 'b';
				g->m_cColor = 'r';
				rightrotate(g);
			}
		}
		else
		{
			if (g->m_pLeft != NULL)
			{
				u = g->m_pLeft;
				if (u->m_cColor == 'r')
				{
					t->m_pParent->m_cColor = 'b';
					u->m_cColor = 'b';
					g->m_cColor = 'r';
					t = g;
				}
			}
			else
			{
				if (t->m_pParent->m_pLeft == t)
				{
					t = t->m_pParent;
					rightrotate(t);
				}
				t->m_pParent->m_cColor = 'b';
				g->m_cColor = 'r';
				leftrotate(g);
			}
		}
		m_pRootNode->m_cColor = 'b';
	}
}

void RBtree::del()
{
	if (m_pRootNode == NULL)
	{
		cout << "\nEmpty Tree.";
		return;
	}
	int x;
	cout << "\nENter the m_iKey of the TNode to be deleted: ";
	cin >> x;
	TNode *p;
	p = m_pRootNode;
	TNode *y = NULL;
	TNode *q = NULL;
	int found = 0;
	while(p != NULL && found == 0)
	{
		if (p->m_iKey == x)
			found = 1;
		if (found == 0)
		{
			if (p->m_iKey < x)
				p = p->m_pRight;
			else
				p = p->m_pLeft;
		}
	}
	if (found == 0)
	{
		cout << "\nElement Not Found. ";
		return;
	}
	else
	{
		cout << "\nDeleted Element: " << p->m_iKey;
		cout << "\nColour: ";
		if (p->m_cColor == 'b')
			cout << "Black\n";
		else
			cout << "Red\n";

		if (p->m_pParent != NULL)
			cout << "\nParent:" << p->m_pParent->m_iKey;
		else
			cout << "\nThere is no m_pParent of the TNode. ";
		if (p->m_pRight != NULL)
			cout << "\nRight Child: " << p->m_pRight->m_iKey;
		else
			cout << "\nThere is no m_pRight child of the TNode. ";
		if (p->m_pLeft != NULL)
			cout << "\nLeft Child: " << p->m_pLeft->m_iKey;
		else
			cout << "\nThere is no m_pLeft child of the TNode. ";
		cout << "\n Node Deleted. ";
		if (p->m_pLeft == NULL || p->m_pRight == NULL)
			y = p;
		else
			y = successor(p);
		if (y->m_pLeft != NULL)
			q = y->m_pLeft;
		else
		{
			if (y->m_pRight != NULL)
				q = y->m_pRight;
			else
				q = NULL;
		}
		if (q != NULL)
			q->m_pParent = y->m_pParent;
		if (y->m_pParent == NULL)
			m_pRootNode = q;
		else
		{
			if (y == y->m_pParent->m_pLeft)
				y->m_pParent->m_pLeft = q;
			else
				y->m_pParent->m_pRight = q;
		}
		if (y != p)
		{
			p->m_cColor = y->m_cColor;
			p->m_iKey = y->m_iKey;
		}
		if (y->m_cColor == 'b')
			delfix(q);
	}
}