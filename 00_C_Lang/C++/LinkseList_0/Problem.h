#pragma once
/////////////////원형 연결 리스트 //////////////////////////
//사용자 정의 함수 사용
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

