#pragma once
#pragma once
#include "Header.h"

template< class Child >
class TTemplateMap
{
public:
	typedef map <int, Child*>					TemplateMap;
	typedef typename TemplateMap::iterator		TemplateMapItor;
	TemplateMapItor								TItor;
	TemplateMap									TMap;
	int											m_iCurIndex;
public:
	// �ʱ�ȭ �Ѵ�.
	bool		Init();
	// �Ҵ�� �����͸� ����Ͽ� �����Ѵ�.
	int			Add(Child*);
	// ��ü�̸����� Child ��ü�� �Ҵ��Ͽ� �����Ѵ�.
	int			Add(const TCHAR *pFileName);
	// �ε����� ���Ͽ� ��ü�� ���Ϲ޴´�.
	Child*		GetPtr(DWORD index);
	// ��ü�̸����� ��ü�� ���Ϲ޴´�.
	Child*		GetPtr(const TCHAR* szName);
	// ��ü �����ͷ� ����� �ε����� ���Ϲ޴´�.
	int			GetID(Child*);
	// ��ü�̸����� ����� �ε����� ���Ϲ޴´�.
	int			GetID(const TCHAR* szName);
	// ��ü ����� ������ ��´�.
	int			Count();
	// ��ü ����� ��ü�� �����Ѵ�.
	bool		Release();
public:
	TTemplateMap();
	~TTemplateMap();
};
template < class Child >
int TTemplateMap< Child >::GetID(Child* pChild)
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
int TTemplateMap< Child >::GetID(const TCHAR* szName)
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
bool TTemplateMap< Child >::Init()
{
	m_iCurIndex = 0;
	TMap.clear();
	return true;
}
template < class Child >
int TTemplateMap< Child >::Count()
{
	return (int)TMap.size();
}
template < class Child >
bool TTemplateMap< Child >::Release()
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
int TTemplateMap< Child >::Add(Child* pChild)
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
int TTemplateMap< Child >::Add(const TCHAR *pFileName)
{
	// ���� ���� 
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
Child *TTemplateMap< Child >::GetPtr(DWORD dwIndex)
{
	TemplateMapItor itor = TMap.find(dwIndex);
	if (itor == TMap.end()) return NULL;
	Child *pPoint = (*itor).second;
	return pPoint;
}
template < class Child >
Child* TTemplateMap< Child >::GetPtr(const TCHAR* szName)
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
TTemplateMap< Child >::TTemplateMap()
{
	m_iCurIndex = 0;
	TMap.clear();
}

template < class Child >
TTemplateMap< Child >::~TTemplateMap()
{
	Release();
}

template<class T> class TSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleInstance;
		return theSingleInstance;
	}
	static T* GetInstancePtr()
	{
		static T theSingleInstance;
		return &theSingleInstance;
	}
};