#include "Problem.h"

///////////////////////////////////////////////////
//원형 링크드 리스트를 작성한다.
///////////////////////////////////////////////////
_NODE * CircularLinkedList(char *strList)
{
	_NODE *pNode = 0;

	pNode = (_NODE*)malloc(iNodeSize);
	pNode->cName = strList[0];
	g_pHead = pNode;

	int iMaxCount = strlen(strList);
	for (int iCount = 1; iCount < iMaxCount; iCount++)
	{
		pNode->pNext = (_NODE*)malloc(iNodeSize);
		pNode = pNode->pNext;
		pNode->cName = strList[iCount];
	}
	pNode->pNext = g_pHead;
	return g_pHead;
}
/////////////////////////////////////////////////////////////
//노드를 삭제한다
////////////////////////////////////////////////////////////

_NODE*NextNodeDelete(_NODE*pNode)
{
	_NODE *pDelNode = pNode->pNext;
	pNode->pNext = pDelNode->pNext;
	free(pDelNode);
	return pNode->pNext;
}
////////////////////////////////////////////////////////////
//요셉의 문제를 계산한다
////////////////////////////////////////////////////////////
void JosephProblem(_NODE* pNode, int n)
{
	_NODE *pPreNode = 0;
	while (pNode != pNode->pNext)
	{
		for (int i = 0; i < n - 1; i++)
		{
			pPreNode = pNode;
			pNode = pNode->pNext;
		}
		printf("%c", pNode->cName);
		pNode = NextNodeDelete(pPreNode);
	}
	printf("\n\n탈출할 장병: %c\n", pNode->cName);
	free(pNode);
}
///////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////
void main()
{
	char strList[100];
	int iCount;
	printf("장병 문자열...?");
	scanf("%s", &strList);
	//fflush(stdin);
	char c;
	while ((c = getchar()) != '\n'&&c != EOF);

	printf("몇명 간격...?");
	scanf("%d", &iCount);

	iNodeSize = sizeof(_NODE);

	_NODE* pLeafNode = CircularLinkedList(strList);

	JosephProblem(pLeafNode, iCount);
}