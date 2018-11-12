#include "value.h"


value::value(TCHAR* pData)
{
	int iLength = _tcslen(pData) + 1;
	int iSize = sizeof(TCHAR)*iLength;
	this->m_szValue = new TCHAR[iSize];
	_tcscpy_s(m_szValue, iSize, pData);
	m_pNext = NULL;
}


value::~value()
{
	delete m_szValue;
}


