#pragma once
#include <stdlib.h>
#include <iostream>
#include <time.h>

#define MAX_NUM 100
int g_iStackBuffer[MAX_NUM];
int g_iTopStack = 0;

int g_iQueueBuffer[MAX_NUM];
int g_iRearQueue = 0;
int g_iFrontQueue = 0;
bool g_bFlagQueue = false;

void Swap(int *a, int *b)
{
	if (*a > *b)
	{
		int t = *a;
		*a = *b;
		*b = t;
	}
}

/////////////////////////////
//statk
/////////////////////////////

void InitStack()
{
	g_iTopStack = 0;
}

void StackPush(int i)
{
	if (g_iTopStack >= MAX_NUM)
	{
		std::cout << "g_iStackBuffer Full" << std::endl;
		return;
	}
	else
	{
		g_iStackBuffer[g_iTopStack++] = i;
	}
}
int StackPop()
{
	if (g_iTopStack == 0)
	{
		return 0;
	}
	else
		return g_iStackBuffer[--g_iTopStack];
}

int IsStatkEmpty()
{
	if (g_iTopStack == 0)
	{
		return 1;
	}
	else
		return 0;
}
//////////////////////////////////
//Queue
//////////////////////////////////

void InitQueue()
{
	g_iRearQueue = 0;
	g_iFrontQueue = 0;
}
//0��° ���� ���� �������� �ִ´�.
void QueuePush(int i)
{
	if (g_bFlagQueue == true)
	{
		std::cout << "g_iQueueBuffer Full" << std::endl;
		return;
	}
	g_iRearQueue = (g_iRearQueue + 1) % MAX_NUM;
	if (g_iFrontQueue == g_iRearQueue)
	{
		//���ڵ尡 ������ ��� ����ĭ�� �����Ͽ� �ִ´�.
		g_bFlagQueue = true;
	}
	g_iQueueBuffer[g_iRearQueue] = i;
}

int QueuePop()
{
	if (g_iFrontQueue == g_iRearQueue && g_bFlagQueue == false)
	{
		std::cout << "g_iQueueBuffer Empty" << std::endl;
		return 0;
	}
	g_bFlagQueue = false;
	g_iFrontQueue = (g_iFrontQueue + 1) % MAX_NUM;
	return g_iQueueBuffer[g_iFrontQueue];
}
int IsQueueEmpty()
{
	if (g_iFrontQueue == g_iRearQueue)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


