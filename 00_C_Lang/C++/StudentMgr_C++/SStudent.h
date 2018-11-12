#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <conio.h>
using namespace std;

struct StudentData
{
	char strName[4];
	int iindex;
	int iKor;
	int iEng;
	int iMat;
	int iTotal;
	float Average;
};

class SStudent
{
public:
	void inputData(int Cnt);
	StudentData GetData();
	void SetData(char strName[],
		int iindex,
		int iKor,
		int iEng,
		int iMat,
		int iTotal,
		float Average);
	void Print();
private:
	StudentData sData;

public:
	SStudent();
	~SStudent();
};


 struct Node
{
	SStudent iData;
	Node* pNext;
	Node(SStudent temp)
	{
		memcpy(&iData, &temp,sizeof(SStudent));
	};
};
enum Work
{
	DataNew = 1,
	DataPrint,
	IndexFind,
	SaveData,
	LoadData,
	AddData,
	DelData,
	EXIT,
};
