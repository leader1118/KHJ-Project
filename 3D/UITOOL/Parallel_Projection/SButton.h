#pragma once
#include "SActor.h"
class SButton : public SActor
{
public:
	vector<PNCT_VERTEX>	m_tVertexList;
	SActor				m_Actor[9];
	SPoint				m_cpPoint[16];
public:
	D3DXVECTOR3 Gen(float x, float y);
	void MoveX(float fDis);
	void MoveY(float fDis);
	void SetVertexData();
public:
	bool SetData(RECT rt, float fScaleX0 = 1.0f,float fScaleX1=1.0f, 
		float fScaleY0 = 1.0f, float fScaleY1 = 1.0f,
		float fOffsetU0 = 1.0f, float fOffsetU1 = 1.0f,
		float fOffsetV0 = 1.0f, float fOffsetV1 = 1.0f);
	bool Create(ID3D11Device* pd3dDevice,
		const TCHAR* pVsFile,
		const TCHAR* pPsFile,
		const TCHAR* pTexFile);
	bool Render(ID3D11DeviceContext* pContext,UINT iVertexSize);
	bool PostRender(ID3D11DeviceContext* pContext);
	bool Init();
	bool Frame(float fGameTimer, float fFps);
	bool Release();

public:
	SButton();
	virtual ~SButton();
};

