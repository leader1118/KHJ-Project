#pragma once
#include "KHJ_AnimObj.h"

class KHJ_Writer : public KHJ_AnimObj, public TSingleton<KHJ_Writer>
{
private:
	friend class TSingleton<KHJ_Writer>;
public:
	FILE* m_pStream; // 출력 파일 포인터
	TSTR m_strFileName; // 출력 할 파일명
public:
	bool Init(TSTR strFileName, Interface* pMax); // 초기화
	bool KHJExport(); // 파일 출력
	bool Release(); // 메모리 소멸 및 해제
	// 출력 파일 지정 대화상자
	TCHAR* SaveFileDlg(TCHAR* szExt, TCHAR* szTitle = _T("KHJExporter"));
	void ExpScene();
	void ExpMaterial();
	void ExpObject();
	int ExpMesh(FILE* fp, SMesh* pMesh, int iMtrl = -1, int iAddCount = 0);
	void ExpAnimation(SMesh* pMesh);
	void ExpTexture(vector<STexMap>& TexMap);
	int IsEqulVertexList(vector<PNCT_VERTEX>& VertexArray, PNCT_VERTEX& Vertex);
	int SetUniqueBuffer(SMesh* pMesh, int iMtrl, int iStartTir, vector<PNCT_VERTEX>& VertexArray, vector<int>& IndexArray);
	void matExport();
public:
	KHJ_Writer();
	KHJ_Writer
};
#define I_Writer KHJ_Writer::GetInstance()

