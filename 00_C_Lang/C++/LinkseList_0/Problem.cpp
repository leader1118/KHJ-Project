#include "Problem.h"

///////////////////////////////////////////////////
//���� ��ũ�� ����Ʈ�� �ۼ��Ѵ�.
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
//��带 �����Ѵ�
////////////////////////////////////////////////////////////

_NODE*NextNodeDelete(_NODE*pNode)
{
	_NODE *pDelNode = pNode->pNext;
	pNode->pNext = pDelNode->pNext;
	free(pDelNode);
	return pNode->pNext;
}
////////////////////////////////////////////////////////////
//����� ������ ����Ѵ�
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
	printf("\n\nŻ���� �庴: %c\n", pNode->cName);
	free(pNode);
}
///////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////
void main()
{
	char strList[100];
	int iCount;
	printf("�庴 ���ڿ�...?");
	scanf("%s", &strList);
	//fflush(stdin);
	char c;
	while ((c = getchar()) != '\n'&&c != EOF);

	printf("��� ����...?");
	scanf("%d", &iCount);

	iNodeSize = sizeof(_NODE);

	_NODE* pLeafNode = CircularLinkedList(strList);

	JosephProblem(pLeafNode, iCount);
}