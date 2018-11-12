#include "Token.h"
void Token::Show()
{
	value* pData = m_pToken;
	for (int i = 0; i < m_iSize; i++)
	{
		std::wcout << pData->m_szValue << endl;
		pData = pData->m_pNext;
	}
}


Token::Token(TCHAR* pData)
{
	m_iSize = 0;
	TCHAR* temp;
	TCHAR* pszNextToken = 0;

	temp = _tcstok_s(pData, SPA, &pszNextToken);
	if (temp != NULL)
	{
		m_pToken = new value(temp);
		value* pLink = m_pToken;
		for (m_iSize = 1;
			temp = _tcstok_s(0, SPA, &pszNextToken);
			m_iSize++)
		{
			pLink->m_pNext = new value(temp);
			pLink = pLink->m_pNext;
		}
	}
}





Token::~Token()
{
	value* pDel;
	value* pLink = m_pToken;
	while (pLink != 0)
	{
		pDel = pLink;
		pLink = pLink->m_pNext;
		delete pDel;
	}
}
