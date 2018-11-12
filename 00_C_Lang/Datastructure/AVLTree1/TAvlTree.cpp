#include "TAvlTree.h"

int TAvlTree::getHeight(Node* node)
{
	if (node == nullptr) return 0;
	return node->height;
}
Node* TAvlTree::updateHeight(Node* node)
{
	node->height = 1 + max(getHeight(Node->left), getHeight(Node->right));
	return node;
}
Node* TAvlTree::insert(Node* root, int value)
{
	if (root == nullptr)
		return new Node(value);
	if (root->value < value)
	{
		root->right = insert(root->right, value);
	}
	else if (root->value == value)
	{
		cout << "value: " << value << "No duplicate vertex allowed." << endl;
		return root;
	}
	else
	{
		root->left = insert(root->left, value);
	}
	root = updateHeight(root);

	int balance_factor = getHeight(root->left) - getHeight(root->right);

	//LR rotation
	if (balance_factor > 1 && root->left->value < value)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	//RR rotation
	else if (balance_factor > 1 && root->left->value > value)
	{
		return rightRotate(root);
	}
	//LL rotation
	else if (balance_factor < -1 && root->right->value < value)
	{
		return leftRotate(root);
	}
	//RL rotation
	else if (balance_factor<-1 && root->right->value>value)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
}
Node* TAvlTree::leftRotate(Node* root)
{
	Node* x = root->right;
	Node* t = x->left;

	root->right = t;
	x->left = root;

	//update height
	x = updateHeight(x);
	root = updateHeight(root);

	return x;
}
Node* TAvlTree::rightRotate(Node* root)
{
	Node* x = root->left;
	Node* t = x->right;

	root->left = t;
	x->right = root;

	//update height

	root = updateHeight(root);
	x = updateHeight(x);
	return x;
}
TAvlTree::TAvlTree()
{
}


TAvlTree::~TAvlTree()
{
}
