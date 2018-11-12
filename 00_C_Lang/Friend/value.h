#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <tchar.h>
#include <vector>
#define SPA _T(" ")
using namespace::std;

class Token;


class value
{
public:
	TCHAR * m_szValue;
	value*  m_pNext;
	friend class Token;
public:
	value(TCHAR*);
public:
	~value();
};

