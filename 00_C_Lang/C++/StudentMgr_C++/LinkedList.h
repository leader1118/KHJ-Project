#pragma once
#include "SStudent.h"
class LinkedList
{
public:
	void Insert();
	void Delete();
	void Delete(Node*_preNode);
	void Find();
	void Insert(Node* _newNode);
	Node* Head;
	Node* Tail;
	int MAX;
	void printAll();
	void save();
	void Load();
	Node* cur;
public:
	LinkedList();
	~LinkedList();
};

