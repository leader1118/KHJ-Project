#pragma once
#include "S_KHJGlobal.h"
// 입출력 클래스
class S_KHJWriter : public S_KHJGlobal 
{
public:
	FILE* m_pStream;
public:
	void Run();
	void Release();
	void Exeporter();
	void GetTexture(Mtl* pSubmtl, xMtrlerial& xMtrl);
public:
	S_KHJWriter();
	virtual ~S_KHJWriter();
};

