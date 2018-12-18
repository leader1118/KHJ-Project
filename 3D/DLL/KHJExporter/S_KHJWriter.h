#pragma once
#include "S_KHJGlobal.h"
// ����� Ŭ����
class S_KHJWriter : public S_KHJGlobal 
{
public:
	FILE* m_pStream;
public:
	void Run();
	void Release();
	void Exeporter();
	void GetTexture(Mtl* pSubmtl, xMtrlerial& xMtrl);
	void GetMesh(INode* pNode, xGeomMesh& xMesh);
	void GetTriObjectFromNode();
public:
	S_KHJWriter();
	virtual ~S_KHJWriter();
};

