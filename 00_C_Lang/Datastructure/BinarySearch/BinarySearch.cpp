#include <iostream>
#define SAFE_NEW(p,N) {if(!p) p=new N;}
//#define SAFE_NEW_ARRAY(p,N,C) {if(!p) p=new N[C]; if(p) memset(p,0,sizeof(N)*C);}
#define SAFE_NEW_VALUE(p,N,v) {if(!p) p=new N(v);}
#define SAFE_DEL(p) {if(p)delete p; (p) = NULL; }
#define SAFE_ZERO(p) {p=0;};
struct TNode
{
	int  m_iValue;
	int  m_iDepth;
	TNode* m_pLeft;
	TNode* m_pRight;
	TNode(int idata) : m_iValue(idata), m_pLeft(0), m_pRight(0), m_iDepth(0) {};

};
TNode* g_pRoot = NULL;
int g_iIndex = 0;
void BinaryNode(TNode* pParentNode, int idata)
{
	if (pParentNode == 0)return;
	// iData > parent --> 오른쪽 노드 추가
	// 왼쪽노드 추가 (반대경우)
	if (pParentNode->m_iValue > idata)
	{
		if (pParentNode->m_pLeft == 0)
		{
			pParentNode->m_pLeft = new TNode(idata);
		}
		else
		{
			BinaryNode(pParentNode->m_pLeft, idata);
		}

	}
	else
	{
		if (pParentNode->m_pRight == 0)
		{
			pParentNode->m_pRight = new TNode(idata);
		}
		else
		{
			BinaryNode(pParentNode->m_pRight, idata);
		}
	}
}
//void Build(TNode* pParentNode)
//{
//	std::cout << pParentNode->m_iValue << std::endl;
//
//	if (ADD(pParentNode))
//	{
//
//		Build(pParentNode->m_pLeft);
//		Build(pParentNode->m_pRight);
//	}
//}
void PRINT(TNode* pParentNode)
{

	if (pParentNode != NULL)
	{
		std::cout << pParentNode->m_iValue << std::endl; //전위 preorder
		Build(pParentNode->m_pLeft);
		//std::cout << pParentNode->m_iValue << std::endl; //중위 inorder
		Build(pParentNode->m_pRight);
		//std::cout << pParentNode->m_iValue << std::endl; //후위 postorder
	}
}
void DELALL(TNode* pParentNode)
{

	if (pParentNode == NULL)return;
	DELALL(pParentNode->m_pLeft);
	DELALL(pParentNode->m_pRight);
	SAFE_DEL(pParentNode);
}
int g_iData[10] = { 5,0,4,7,8,3,9,2,6,1 };
void main()
{
	g_pRoot = new TNode(0);
	TNode* pNode = g_pRoot;

	SAFE_NEW_VALUE(g_pRoot, TNode, g_iData[g_iIndex++]);
	for (int i = 1; i < 10; i++)
	{
		BinaryNode(g_pRoot, g_iData[i]);
	}
	//Build(g_pRoot);
	PRINT(g_pRoot);
	DELALL(g_pRoot);
	SAFE_ZERO(g_pRoot)
		getchar();
}