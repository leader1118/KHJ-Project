#pragma once
#include <iostream>
#include <math.h>
using namespace std;
#ifndef max
#define max(a,b)        ((a)>(b)?(a):(b))
#endif
class Node
{
public:
	Node * left;
	Node* right;
	int value;
	int height;
	Node(int value)
	{
		this->value = value;
		left = right = nullptr;
		height = 1;
	}
};
class TAvlTree
{
public:
	int  getHeight(Node* node);
	Node* updateHeight(Node* node);
	Node* insert(Node* root, int value);
	Node* leftRotate(Node* root);
	Node* rightRotate(Node* root);
	void printAll(Node* root);
public:
	TAvlTree();
	~TAvlTree();
};

