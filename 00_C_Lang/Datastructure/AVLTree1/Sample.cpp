#include "TAvlTree.h"

int main()
{
	TAvlTree avl;
	Node* root = nullptr;
	// ������� ���̰� =1 �̸� , ��Ʈ�� ���� ũ��.
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