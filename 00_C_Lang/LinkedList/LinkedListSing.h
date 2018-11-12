#pragma once
#include <iostream>
#include <conio.h>
using namespace std;

struct Node
{
	Node* m_pNext;
	int iData;
	int iCount;
	Node (int pData) { iData = pData; };
};

class LinkedListSing
{
public:
	Node* m_Head;
	Node* m_Tail;
	int   i_MAX;
public:
	void Add();
	void Del(int aData);
	void print();
	void Find(int sData);
	
public:
	LinkedListSing();
	~LinkedListSing();
};

