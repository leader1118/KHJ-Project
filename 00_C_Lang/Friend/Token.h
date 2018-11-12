#pragma once
#include "value.h"


class Token
{
public:
	value * m_pToken;
	int     m_iSize;
public:
	void Show();

	Token(TCHAR* pData);
	~Token();
};

