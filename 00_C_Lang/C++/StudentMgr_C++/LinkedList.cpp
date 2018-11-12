#include "LinkedList.h"
#include "SStudent.h"

void LinkedList::Insert()//»ðÀÔ
{
	if (Head == NULL)
	{
		SStudent mData;
		mData.inputData(++MAX);
		Node* aData = new Node(mData);
		Head = aData;
		Tail = Head;
		Tail->pNext = NULL;

		return;
	}
	SStudent qData;
	qData.inputData(++MAX);
	Node* aData = new Node(qData);
	Tail->pNext = aData;
	Tail = Tail->pNext;
	Tail->pNext = NULL;
}
void LinkedList::Delete()
{
	if (Head == NULL)
		return;
	else if (Head->pNext == NULL)
		delete Head;
	int select = 0;
	cin >> select;
	Node* tamp = Head;
	while (tamp->pNext != NULL)
	{
		if (tamp->iData.GetData().iindex == select)
		{
			break;
		}
	}
	Node* delNode = tamp->pNext;
	Node* nextNode = delNode->pNext;
	delete delNode;
	tamp->pNext = nextNode;
}
void LinkedList::Delete(Node* _preNode)
{
	if (Head == NULL)
	{
		return;
	}
	else if (_preNode == NULL || _preNode->pNext == NULL)
	{
		return;
	}

	Node* pDelNode = _preNode->pNext;
	Node* pNextNode = pDelNode->pNext;
	delete pDelNode;
	MAX--;
	_preNode->pNext = pNextNode;
}
void LinkedList::Find()
{
	if (Head == NULL)
		return;

	int select = 0;
	cin >> select;
	Node* tamp = Head;
	while (tamp->pNext != NULL)
	{
		if (tamp->iData.GetData().iindex == select)
		{
			break;
		}
		tamp = tamp->pNext;
	}
	tamp->iData.Print();
}
void LinkedList::printAll()
{
	if (Head == NULL)
		return;
	
	
	Node* tamp = Head;
	for (int i = 0; i < MAX; i++)
	{
		tamp->iData.Print();
		tamp = tamp->pNext;
	}

}
void LinkedList::save()
{
	FILE* fp = NULL;
	fp = fopen("DEMO.txt", "wt");
	cur = Head;
	fprintf(fp, "%d", MAX);
	for (int i = 0; i < MAX; i++)
	{
		fprintf
		(fp,
			"\n%3d %8s %7d %7d %7d %7d %10.4f",
			cur->iData.GetData().iindex,
			cur->iData.GetData().strName,
			cur->iData.GetData().iKor,
			cur->iData.GetData().iEng,
			cur->iData.GetData().iMat,
			cur->iData.GetData().iTotal,
			cur->iData.GetData().Average
		);
		cur = cur->pNext;
	}
	fclose(fp);
}
void LinkedList::Load()
{
	FILE* fp;
	fp = fopen("DEMO.txt", "rt");
	if (fp == NULL)
	{
		return ;
	}

	if (Head != NULL)
	{
		while (Head->pNext != NULL)
		{
			delete(Head);
		}
		Tail = Head;

		delete Head;
	}

	//fscanf(fp, "%d", &MAX);
	if (Head == NULL)
	{
		SStudent cStuTemp;
		char   szTempName[255] = { 0, };
		int      iTemp[6] = { 0, };
		float   fTemp = 0.0f;
		fscanf(fp, "%d", &MAX);
		for (int i = 0; i < MAX; i++)
		{
			fscanf(fp, "%d %s %d %d %d %d %f",
				&iTemp[0],
				szTempName,
				&iTemp[1],
				&iTemp[2],
				&iTemp[3],
				&iTemp[4],
				&fTemp);


			cStuTemp.SetData(szTempName,iTemp[0],iTemp[1],iTemp[2],iTemp[3],iTemp[4],fTemp);

			Node* pTempNode = new Node(cStuTemp);
			Insert(pTempNode);
		}
	}

	fclose(fp);
}
void LinkedList::Insert(Node* _newNode)
{
	if (Head == NULL)
	{
		Node* pFirstNode = new Node(_newNode->iData);
		Head = pFirstNode;
		Tail = Head;
		Tail->pNext = NULL;

		return;
	}

	Node* pNewNode = new Node(_newNode->iData);
	Tail->pNext = _newNode;
	Tail = Tail->pNext;
	Tail->pNext = NULL;

}
LinkedList::LinkedList()
{
	Head = NULL;
	Tail = NULL;
	MAX = 0;
	cur = NULL;
}


LinkedList::~LinkedList()
{
}
