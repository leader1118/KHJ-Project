#pragma once
#ifndef __BINARY_TREE3_H__
#define __BINARY_TREE3_H__

typedef int BTData;

typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode* left;
	struct _bTreeNode* right;
}BTreeNode;

BTreeNode* MakeBTreeNode(void);
BTData GetData(BTreeNode* bt);
void SetData(BTreeNode* bt, BTData data);

BTreeNode* GetLeftSubTree(BTreeNode* bt);
BTreeNode* GetRightSubTree(BTreeNode* bt);

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub);
void MakeRightSubTree(BTreeNode* main, BTreeNode* sub);

typedef void VisitFuncPtr(BTData data);

void PreorderTraverse(BTreeNode* bt, VisitFuncPtr action);
void InorderTraverse(BTreeNode* bt, VisitFuncPtr action);
void PostorderTraverse(BTreeNode* bt, VisitFuncPtr action);

//���� �ڽ� ��� ����, ���ŵ� ����� �ּ� ���� ��ȯ�ȴ�.
BTreeNode* RemoveLeftSubTree(BTreeNode* bt);

//������ �ڽ� ��� ����, ���ŵ� ����� �ּ� ���� ��ȯ�ȴ�
BTreeNode* RemoveRightSubTree(BTreeNode* bt);

//�޸� �Ҹ��� �������� �ʰ� main�� ���� �ڽ� ��带 �����Ѵ�.
void ChangeLeftSubTree(BTreeNode* main, BTreeNode* sub);

//�޸� �Ҹ��� �������� �ʰ� main�� ������ �ڽ� ��带 �����Ѵ�.
void ChangeRightSubTree(BTreeNode* main, BTreeNode* sub);


typedef BTData BSTData;

//���� Ž�� Ʈ���� ���� �� �ʱ�ȭ
void BSTMakeAndInit(BTreeNode** pRoot);

//��忡 ����� ������ ��ȯ
BSTData BStGetNodeData(BTreeNode* bst);

//���� Ž�� Ʈ���� ������� ������ ����(����� �������� ����)
void BSTInsert(BTreeNode**pRoot, BSTData data);

//���� Ž�� Ʈ���� ������� ������ Ž��
BTreeNode* BSTSearch(BTreeNode* bst, BSTData target);

//Ʈ������ ��带 �����ϰ� ���ŵ� ����� �ּҰ��� ��ȯ�Ѵ�.
BTreeNode* BSTRemove(BTreeNode**pRoot, BSTData Target);

//���� Ž��Ʈ���� ����� ��� ����� �����͸� ����Ѵ�.
void BSTSHowAll(BTreeNode* bst);
#endif
