#include <iostream>
#include <cstdlib>
#include "TAvlTree.h"
#include "TBTree.h"

BTreeNode* MakeBTreeNode(void)
{
	BTreeNode* nd = (BTreeNode*)malloc(sizeof(BTreeNode));

	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

BTData GetData(BTreeNode* bt)
{
	return bt->data;
}

void SetData(BTreeNode* bt, BTData data)
{
	bt->data = data;
}

BTreeNode* GetLeftSubTree(BTreeNode* bt)
{
	return bt->left;
}

BTreeNode* GetRightSubTree(BTreeNode* bt)
{
	return bt->right;
}

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->left != NULL)
		free(main->left);

	main->left = sub;
}

void MakeRightSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->right != NULL)
		free(main->right);

	main->right = sub;
}

void PreorderTraverse(BTreeNode* bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;

	action(bt->data);
	PreorderTraverse(bt->left, action);
	PreorderTraverse(bt->right, action);
}

void InorderTraverse(BTreeNode* bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;

	InorderTraverse(bt->left, action);
	action(bt->data);
	InorderTraverse(bt->right, action);
}

void PostorderTraverse(BTreeNode* bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;

	PostorderTraverse(bt->left, action);
	PostorderTraverse(bt->right, action);
	action(bt->data);
}

BTreeNode* RemoveLeftSubTree(BTreeNode* bt)
{
	BTreeNode* delNode = 0;

	if (bt != NULL)
	{
		delNode = bt->left;
		bt->left = NULL;
	}
	return delNode;
}

BTreeNode* RemoveRightSubTree(BTreeNode* bt)
{
	BTreeNode* delNode = 0;

	if (bt != NULL)
	{
		delNode = bt->right;
		bt->right = NULL;
	}
	return delNode;
}

void ChangeLeftSubTree(BTreeNode* main, BTreeNode* sub)
{
	main->left = sub;
}

void ChangeRightSubTree(BTreeNode* main, BTreeNode* sub)
{
	main->right = sub;
}


void BSTMakeAndInit(BTreeNode** pRoot)
{
	*pRoot = NULL;
}

BSTData BSTGetNodeData(BTreeNode* bst)
{
	return GetData(bst);
}

void BSTInsert(BTreeNode** pRoot, BSTData data)
{
	BTreeNode* pNode = NULL; //parent node
	BTreeNode* cNode = *pRoot; //current node
	BTreeNode* nNode = NULL; //new node

	                                     //���ο� ��尡 �߰��� ��ġ�� ã�´�.
	while (cNode != NULL)
	{
		if (data == GetData(cNode))
			return; //Ű�� �ߺ��� ������� ����

		pNode = cNode;

		if (GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	//pNode�� ���� ��忡 �߰��� �� ����� ����
	nNode = MakeBTreeNode();      //�� ����� ����
	SetData(nNode, data);         //�� ��忡 ������ ����
	             
	                              //pNode�� ���� ��忡 �� ��带 �߰�
	if (pNode != NULL)
	{
		if (data < GetData(pNode))
			MakeLeftSubTree(pNode, nNode);
		else
			MakeRightSubTree(pNode, nNode);
	}
	else // �� ��尡 ��Ʈ �����
	{
		*pRoot = nNode;
	}
	*pRoot = Rebalance(pRoot); //��� �߰� �� ���뷱��
}

BTreeNode* BstSearch(BTreeNode* bst, BSTData target)
{
	BTreeNode* cNode = bst; // current node
	BSTData cd;    //current data

	while (cNode != NULL)
	{
		cd = GetData(cNode);

		if (target == cd)
			return cNode;
		else if (target < cd)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	return NULL;
}

BTreeNode* BSTRemove(BTreeNode** pRoot, BSTData target)
{
	//���� ����� ��Ʈ ����� ��츦 ������ ����ؾ��Ѵ�.

	BTreeNode* pVRoot = MakeBTreeNode(); //���� ��Ʈ ���;

	BTreeNode* pNode = pVRoot;   //parent node
	BTreeNode* cNode = *pRoot;   //current node
	BTreeNode* dNode;      //delete node

	         //��Ʈ ��带 pVRoot�� ����Ű�� ����� ������ ���� ��尡 �ǰ��Ѵ�
	ChangeRightSubTree(pVRoot, *pRoot);

	//���� ����� ������ ��� Ž��
	while (cNode != NULL && GetData(cNode) != target)
	{
		pNode = cNode;

		if (target < GetData(cNode))
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}
	if (cNode == NULL) // ���� ����� �������� �ʴ´ٸ�,
		return NULL;

	dNode = cNode; // ���� ����� dNode�� ����Ű�� �Ѵ�.

	// ù ��° ���: ������ ��尡 �ܸ� ����� ���

	if (GetLeftSubTree(pNode) == dNode)
	{
		if (GetLeftSubTree(pNode) == dNode)
			RemoveLeftSubTree(pNode);
		else
			RemoveRightSubTree(pNode);
	}

	//�� ��° ���: �ϳ��� �ڽ� ��带 ���� ���
	else if (GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL)
	{
		BTreeNode* dcNode; //delete node�� �ڽ� ���

		if (GetLeftSubTree(dNode) != NULL)
			dcNode = GetLeftSubTree(dNode);
		else
			dcNode = GetRightSubTree(dNode);
		if (GetLeftSubTree(pNode) == dNode)
			ChangeLeftSubTree(pNode, dcNode);
		else
			ChangeRightSubTree(pNode, dcNode);
	}
	//�� ��° ���: �� ���� �ڽ� ��带 ��� ���� ���
	else
	{
		BTreeNode* mNode = GetRightSubTree(dNode); //mininum node
		BTreeNode* mpNode = dNode;  //mininum node�� �θ� ���
		int delData;

		//������ ��带 ��ü�� ��带 ã�´�.
		while (GetLeftSubTree(mNode) != NULL)
		{
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
		}
		//��ü�� ��忡 ����� ���� ������ ��忡 �����Ѵ�.
		delData = GetData(dNode);   //���� �� ������ ���
		SetData(dNode, GetData(mNode));

		// ��ü�� ����� �θ� ���� �ڽ� ��带 �����Ѵ�.
		if (GetLeftSubTree(mpNode) == mNode)
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
		else
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode));

		dNode = mNode;
		SetData(dNode, delData); // ��� ������ ����
	}

	//������ ��尡 ��Ʈ ����� ��쿡 ���� ó��
	if (GetRightSubTree(pVRoot) != *pRoot)
		*pRoot = GetRightSubTree(pVRoot);

	free(pVRoot);

	*pRoot = Rebalance(pRoot);  //��� ���� �� ���뷱��!
	return dNode;
}

void ShowIntData(int data)
{
	std::cout << data << std::endl;
}

void BSTShowAll(BTreeNode* bst)
{
	InorderTraverse(bst, ShowIntData);
}