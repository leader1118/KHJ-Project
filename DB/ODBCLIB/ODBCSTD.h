#pragma once
#pragma comment (lib,"ODBCLIB.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

extern HINSTANCE g_hInst;