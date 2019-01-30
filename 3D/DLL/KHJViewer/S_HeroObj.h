#pragma once
#include "S_CharMgr.h"

#define MAX_BONE_MATRICES 255

struct CBConstBoneWorld
{
	D3DXMATRIX g_mConstBoneWorld[MAX_BONE_MATRICES];
};

class S_HeroObj : public TModel
{
public:
	int m_iObjectIndex;
	S_Character* m_pChar;
	T_STR m_szName;
	TBoneObj* m_pBoneObject;
	bool m_bConstantBufferType;
	int m_iStartFrame;
	int m_iLastFrame;
	int m_iCurrentFrame;

	float m_fFrame;
	float m_fLerpTime;
	float m_fSpeed;
	D3DXMATRIX m_pMatrix[255];
	CBConstBoneWorld m_cbBoneData;
	ComPtr<ID3D11Buffer> m_pCBConstBoneWorld;
	int m_iMatrixIndex;
	bool m_bBoneRender;
public:
	void SetBoneMatrices(vector<D3DXMATRIX>* pList);
	bool Frame();
	bool Render(ID3D11DeviceContext* pContext);
	void SetActionFrame(int iStart, int iEnd, int iCharacterMatrixIndex = -1, int iModelMatrixIndex = -1);
	HRESULT CreateConstantBuffer();
public:
	S_HeroObj();
	virtual ~S_HeroObj();
};

