#pragma once
#include "S_AnimObj.h"
class S_Writer : public S_AnimObj, public SSingleton<S_Writer>
{
private:
	friend class SSingleton<S_Writer>;
public:
	FILE* m_pStream;
	TSTR m_strFileName;
public:
	bool Init(TSTR strFileName, Interface* pMax);
	bool KHJExport();
	bool Release();
public:
	TCHAR* SaveFileDlg(TCHAR* szExt, TCHAR* szTitle = _T("KHJExporter"));
	void ExpScene();
	void ExpMaterial();
	void ExpObject();
	int ExpMesh(FILE* fp, SMesh* pMesh, int iMtrl = -1, int iAddCount = 0);
	void ExpAnimation(SMesh* pMesh);
	void ExpTexture(vector<STexMap>&TexMap);
	int IsEqulVertexList(vector<PNCT_VERTEX>& VertexArray, PNCT_VERTEX& Vertex);
	int SetUniqueBuffer(SMesh* pMesh, int iMtrl, int iStartTri, vector<PNCT_VERTEX>& VertexArray, vector<int>& IndexArray);
	void matExport();

public:
	S_Writer();
	virtual ~S_Writer();
};

#define I_Writer S_Writer::GetInstance()

