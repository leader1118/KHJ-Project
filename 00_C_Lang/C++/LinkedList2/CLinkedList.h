#pragma once
#include <iostream> // 입출력 헤더 stdio와 같은개념
using namespace std; // std를 입력하지 않고 바로 사용가능

struct Node //구조체 노드
{
	Node* m_pNext; //노드의 멤버변수
	int iData;
	int iCount;
	Node(int pData) { iData = pData; };
};

class CLinkedList
{
public:
	Node * m_Head;
	Node* m_Tail;
	int iMAX;
public:
	void Add(); //더해주는 함수
	void Del(int aData); //삭제하는 함수
	void Print(); //출력하는 함수
	void Find(int sData); //검색하는 함수
public:
	CLinkedList();
	virtual ~CLinkedList();
};

