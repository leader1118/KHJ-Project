#pragma once
#include "S_KHJ_AnimObj.h"

class S_KHJ_Writer : public S_KHJ_AnimObj, public TSingleton<S_KHJ_Writer>
{
private:
	friend class TSingleton<S_KHJ_Writer>;
public:
	FILE* m_pStream; // ��� ���� ������
	TSTR m_strFileName; // ��� �� ���ϸ�
public:
	bool Init(TSTR strFileName, Interface* pMax); // �ʱ�ȭ
	bool KHJExport(); // ���� ���
	bool Release(); // �޸� �Ҹ� �� ����
	// ��� ���� ���� ��ȭ����
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
	S_KHJ_Writer();
	virtual ~S_KHJ_Writer();
};
#define I_Writer S_KHJ_Writer::GetInstance()

