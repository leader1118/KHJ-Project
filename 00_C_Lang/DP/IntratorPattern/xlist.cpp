#include "xlist.h"
#include <iostream>
#include "xiter.h"
using namespace std;

int AbstractList::Count() { return totaICnt_; }


Iterator * LinkedList::CreateIterator()
{
	return new ListIterator(this);
}

void LinkedList::AddNext(Item *pNewItem, Item *pItem)
{
	if (pFirst_ == 0)
		pFirst_=new LinkedItem(pNewItem);
	else if (pItem == 0 || pItem == pFirst_->pData_)
	{
		LinkedItem* pTmp = pFirst_->pNext_;
		pFirst_->pNext_ = new LinkedItem(pNewItem, pTmp);
	}
	else
	{
		LinkedItem* pPrev = 0;
		LinkedItem* pTmp = pFirst_;
		while (pTmp != 0 && pTmp->pData_ != pItem)
		{
			pPrev = pTmp;
			pTmp = pTmp->pNext_;
		}
		if (pTmp != 0)
		{
			LinkedItem* pTmp2 = pTmp->pNext_;
			pTmp->pNext_ = new LinkedItem(pNewItem, pTmp2);
		}
		else
			pPrev->pNext_ = new LinkedItem(pNewItem, 0);
	}
	totaICnt_++;
}

void LinkedList::AddChild(Item* pNewItem, Item* pItem)
{
	AddNext(pNewItem, pItem);
}
void LinkedList::Remove(Item* pItem)
{
	if (pItem == 0)return;

	LinkedItem* pPrev = 0;
	LinkedItem* pTmp = pFirst_;
	while (pTmp != 0 && pTmp->pData_ != pItem)
	{
		pPrev = pTmp;
		pTmp = pTmp->pNext_;
	}

	if (pTmp != 0)
	{
		if (pTmp == pFirst_)
		{
			delete pTmp;
			pFirst_ = 0;
		}
		else
		{
			pPrev->pNext_ = pTmp->pNext_;
			delete pTmp;
		}
		totaICnt_--;
	}
}

Item* LinkedList::GetItem(int pos)
{
	int cnt = 0;
	LinkedItem* pTmp = pFirst_;
	while (pTmp != 0 && cnt != pos)
	{
		pTmp = pTmp->pNext_;
		cnt++;
	}
	if (pTmp != 0)return pTmp->pData_;
	else          return 0;
}


Iterator * TreeList::CreateIterator()
{
	return new TreeIterator(this);
}