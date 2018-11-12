#include <iostream>
#include "TBTree.h"

//LLȸ��
BTreeNode* RotateLL(BTreeNode* bst)
{
	BTreeNode* pNode;
	BTreeNode* cNode;

	pNode = bst;
	cNode = GetLeftSubTree(pNode);

	ChangeLeftSubTree(pNode, GetRightSubTree(cNode));
	ChangeRightSubTree(cNode, pNode);
	return cNode;
}

//RR ȸ��
BTreeNode* RotateRR(BTreeNode* bst)
{
	BTreeNode* pNode;
	BTreeNode* cNode;

	pNode = bst;
	cNode = GetRightSubTree(pNode);

	ChangeRightSubTree(pNode, GetLeftSubTree(cNode));
	ChangeLeftSubTree(cNode, pNode);
	return cNode;
}

//RLȸ��
BTreeNode* RotateRL(BTreeNode* bst)
{
	BTreeNode* pNode;
	BTreeNode* cNode;

	pNode = bst;
	cNode = GetRightSubTree(pNode);

	ChangeRightSubTree(pNode, RotateLL(cNode)); //�κ��� LLȸ��
	return RotateRR(pNode); //RRȸ��
}

//LRȸ��
BTreeNode* RotateLR(BTreeNode* bst)
{
	BTreeNode* pNode;
	BTreeNode* cNode;

	pNode = bst;
	cNode = GetLeftSubTree(pNode);

	ChangeLeftSubTree(pNode, RotateRR(cNode)); // �κ��� RRȸ��
	return RotateLL(pNode); //LLȸ��
}

// Ʈ���� ���̸� ����Ͽ� ��ȯ
int GetHeight(BTreeNode* bst)
{
	int leftH;      //left Height
	int rightH;    //right Height

	if (bst == NULL)
		return 0;

	//���� ���� Ʈ�� ���� ���
	leftH = GetHeight(GetLeftSubTree(bst));

	//������ ���� Ʈ�� ���� ���
	rightH = GetHeight(GetRightSubTree(bst));

	//ū ���� ���̸� ��ȯ�Ѵ�.
	if (leftH > rightH)
		return leftH + 1;
	else
		return rightH + 1;
}

//�� ���� Ʈ���� ������ ���� ��ȯ

int GetHeightDiff(BTreeNode* bst)
{
	int lsh;    //left sub tree height
	int rsh;    // right sub tree height

	if (bst == NULL)
		return 0;

	lsh = GetHeight(GetLeftSubTree(bst));
	rsh = GetHeight(GetRightSubTree(bst));

	return lsh - rsh;
}

//Ʈ���� ������ ��´�

BTreeNode* Rebalance(BTreeNode** pRoot)
{
	int hDiff = GetHeightDiff(*pRoot);

	if (hDiff > 1) //���� ���� Ʈ�� �������� ���̰� 2 �̻� ũ�ٸ�
	{
		if (GetHeightDiff(GetLeftSubTree(*pRoot)) > 0)
			*pRoot = RotateLL(*pRoot);
		else
			*pRoot = RotateLR(*pRoot);
	}

	if (hDiff < -1)// ������ ���� Ʈ�� �������� 2�̻� ũ�ٸ�
	{
		if (GetHeightDiff(GetRightSubTree(*pRoot)) < 0)
			*pRoot = RotateRR(*pRoot);
		else
			*pRoot = RotateRL(*pRoot);
	}
	return *pRoot;
}