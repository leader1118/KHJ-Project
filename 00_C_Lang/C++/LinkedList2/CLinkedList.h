#pragma once
#include <iostream> // ����� ��� stdio�� ��������
using namespace std; // std�� �Է����� �ʰ� �ٷ� ��밡��

struct Node //����ü ���
{
	Node* m_pNext; //����� �������
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
	void Add(); //�����ִ� �Լ�
	void Del(int aData); //�����ϴ� �Լ�
	void Print(); //����ϴ� �Լ�
	void Find(int sData); //�˻��ϴ� �Լ�
public:
	CLinkedList();
	virtual ~CLinkedList();
};

