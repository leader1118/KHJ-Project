#pragma once
/////////////////���� ���� ����Ʈ //////////////////////////
//����� ���� �Լ� ���
//while()
//if~else
//for()
////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
int iNodeSize;
struct _NODE
{
	char  cName;
	struct _NODE *pNext;
};
_NODE *g_pHead = 0;

_NODE *CircularLinkedList(char *strList);
_NODE *NextNodeDelete(_NODE *p);

void JosephProblem(_NODE *p, int n);

