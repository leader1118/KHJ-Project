#include <iostream>
#include "TBTree.h" // 트리의 구조를 확인하기 위해서

int main(void)
{
	BTreeNode* avlRoot;
	BTreeNode* clNode;     //current left node
	BTreeNode* crNode;     //current right node
	BSTMakeAndInit(&avlRoot);

	BSTInsert(&avlRoot, 1);
	BSTInsert(&avlRoot, 2);
	BSTInsert(&avlRoot, 3);
	BSTInsert(&avlRoot, 4);
	BSTInsert(&avlRoot, 5);
	BSTInsert(&avlRoot, 6);
	BSTInsert(&avlRoot, 7);
	BSTInsert(&avlRoot, 8);
	BSTInsert(&avlRoot, 9);

	std::cout << "루트 노드" << "[" << GetData(avlRoot) << "]" << std::endl;

	clNode = GetLeftSubTree(avlRoot);
	crNode = GetRightSubTree(avlRoot);
	std::cout << "왼쪽 1:" << "[" << GetData(clNode) << "]" << "오른쪽 1: " << "[" << GetData(crNode) << "]" << std::endl;

	clNode = GetLeftSubTree(clNode);
	crNode = GetRightSubTree(crNode);
	std::cout << "왼쪽 2:" << "[" << GetData(clNode) << "]" << "오른쪽 2: " << "[" << GetData(crNode) << "]" << std::endl;

	clNode = GetLeftSubTree(clNode);
	crNode = GetRightSubTree(crNode);
	std::cout << "왼쪽 3:" << "[" << GetData(clNode) << "]" << "오른쪽 3: " << "[" << GetData(crNode) << "]" << std::endl;

	clNode = GetLeftSubTree(clNode);
	crNode = GetRightSubTree(crNode);
	std::cout << "왼쪽 4:" << "[" << GetData(clNode) << "]" << "오른쪽 4: " << "[" << GetData(crNode) << "]" << std::endl;

	return 0;
}