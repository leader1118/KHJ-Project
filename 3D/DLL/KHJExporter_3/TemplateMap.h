#pragma once
#include "Header.h"


template<class S> class SSingleton
{
public:
	static S& GetInstance()
	{
		static S theSingleInstance;
		return theSingleInstance;
	}
	static S* GetInstancePtr()
	{
		static S theSingleInstance;
		return &theSingleInstance;
	}
};

template< class Child >
class STemplateMap
{
public:
	typedef map <int, Child*>					TemplateMap;
	typedef typename TemplateMap::iterator		TemplateMapItor;
	TemplateMapItor								TItor;
	TemplateMap									TMap;
	int											m_iCurIndex;
public:
	// 초기화 한다.
	bool		Init();
	// 할당된 포인터를 사용하여 저장한다.
	int			Add(Child*);
	// 객체이름으로 Child 객체를 할당하여 저장한다.
	int			Add(const TCHAR *pFileName);
	// 인덱스를 통하여 객체를 리턴받는다.
	Child*		GetPtr(DWORD index);
	// 객체이름으로 객체를 리턴받는다.
	Child*		GetPtr(const TCHAR* szName);
	// 객체 포인터로 저장된 인덱스를 리턴받는다.
	int			GetID(Child*);
	// 객체이름으로 저장된 인덱스를 리턴받는다.
	int			GetID(const TCHAR* szName);
	// 전체 저장된 갯수를 얻는다.
	int			Count();
	// 전체 저장된 객체를 삭제한다.
	bool		Release();
public:
	STemplateMap();
	~STemplateMap();
};
template < class Child >
int STemplateMap< Child >::GetID(Child* pChild)
{
	int iIndex = -1;
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
	{
		Child *pPoint = (Child *)(*itor).second;
		if (pChild == pPoint)
		{
			iIndex = (*itor).first;
			break;
		}
	}
	return dwIndex;
}
template < class Child >
int STemplateMap< Child >::GetID(const TCHAR* szName)
{
	int iIndex = -1;
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
	{
		Child *pPoint = (Child *)(*itor).second;
		if (!_tcsicmp(pPoint->m_szName.c_str(), szName))
		{
			iIndex = (*itor).first;
			break;
		}
	}
	return iIndex;
}

template < class Child >
bool STemplateMap< Child >::Init()
{
	m_iCurIndex = 0;
	TMap.clear();
	return true;
}
template < class Child >
int STemplateMap< Child >::Count()
{
	return (int)TMap.size();
}
template < class Child >
bool STemplateMap< Child >::Release()
{
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
	{
		Child *pPoint = (Child *)(*itor).second;
		if (pPoint)
			pPoint->Release();
		else
			return false;
		delete pPoint;
	}
	TMap.clear();
	m_iCurIndex = 0;
	return true;
}
template < class Child >
int STemplateMap< Child >::Add(Child* pChild)
{
	if (pChild == NULL)
	{
		return 0;
	}
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
	{
		Child *pPoint = (Child *)(*itor).second;
		if (pPoint == pChild)
		{
			return 0;
		}
	}
	TMap.insert(make_pair(m_iCurIndex++, pChild));
	return m_iCurIndex - 1;
}
template < class Child >
int STemplateMap< Child >::Add(const TCHAR *pFileName)
{
	// 종복 방지 
	if (pFileName)
	{
		TCHAR szFileName[256];
		TCHAR Drive[MAX_PATH];
		TCHAR Dir[MAX_PATH];
		TCHAR FName[MAX_PATH];
		TCHAR Ext[MAX_PATH];
		_tsplitpath_s(pFileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		_stprintf_s(szFileName, _T("%s%s"), FName, Ext);

		for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
			Child *pPoint = (Child *)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szFileName))
			{
				return (*itor).first;
			}
		}
	}

	Child *pPoint = NULL;
	SAFE_NEW(pPoint, Child);
	pPoint->Add(m_iCurIndex, pFileName);
	TMap.insert(make_pair(m_iCurIndex++, pPoint));
	return m_iCurIndex - 1;
}
template < class Child >
Child *STemplateMap< Child >::GetPtr(DWORD dwIndex)
{
	TemplateMapItor itor = TMap.find(dwIndex);
	if (itor == TMap.end()) return NULL;
	Child *pPoint = (*itor).second;
	return pPoint;
}
template < class Child >
Child* STemplateMap< Child >::GetPtr(const TCHAR* szName)
{
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
	{
		Child *pPoint = (Child *)(*itor).second;
		if (!_tcsicmp(pPoint->m_szName.c_str(), szName))
		{
			return pPoint;
		}
	}
	return NULL;
}

template < class Child >
STemplateMap< Child >::STemplateMap()
{
	m_iCurIndex = 0;
	TMap.clear();
}

template < class Child >
STemplateMap< Child >::~STemplateMap()
{
	Release();
}