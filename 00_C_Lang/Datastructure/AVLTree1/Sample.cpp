#include "TAvlTree.h"

int main()
{
	TAvlTree avl;
	Node* root = nullptr;
	// 리프노드 높이가 =1 이면 , 루트가 가장 크다.
	root = avl.insert(root, 1);
	root = avl.insert(root, 1);
	root = avl.insert(root, 1);
	root = avl.insert(root, 1);
	root = avl.insert(root, 1);
	root = avl.insert(root, 1);
	root = avl.insert(root, 1);
	root = avl.insert(root, 1);

	avl.printAll(root);

	return 0;
}