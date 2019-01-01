#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "resource.h"
#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>
#include <maxtypes.h>
#include <utilapi.h>
#include <max.h>
#include <stdmat.h>
#include <decomp.h>
#include <CS/bipexp.h>
#include <CS/phyexp.h>
#include <iskin.h>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <bitset>
#include <limits>
#include <functional>
using namespace std;

#ifndef SAFE_ZERO
#define SAFE_ZERO(A)				{ A = 0; }
#endif

#ifndef SAFE_NEW
#define SAFE_NEW(A, B)				{ if (!A) A = new B; }
#endif 

#ifndef SAFE_DEL
#define SAFE_DEL(A)					{ if (A) delete A; (A)=NULL; }
#endif 

#ifndef SAFE_NEW_ARRAY
#define SAFE_NEW_ARRAY(A, B, C)		{ if (!A && C) A = new B[C]; }
#endif 

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(A)		{ if (A) delete [] A; (A)=NULL; }
#endif 

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }
#endif 

#ifndef SAFE_NEW_CLEAR
#define SAFE_NEW_CLEAR( A, B )			{ if (!A) A = new B; if(A) memset( A, 0, sizeof(B) ); };
#endif 

#ifndef SAFE_NEW_ARRAY_CLEAR
#define NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
#endif

#define RELEASE(A)				{ if(A) { (A)->Release(); } }



typedef basic_string<TCHAR>				T_STR;
typedef basic_string<CHAR>				CHAR_STRING;
typedef vector<basic_string<TCHAR>>		T_STR_VECTOR;
typedef vector<DWORD>					DWORD_VECTOR;

#define KHJ_EXPORT_CLASS_ID Class_ID(0x55533089, 0x59c62028)