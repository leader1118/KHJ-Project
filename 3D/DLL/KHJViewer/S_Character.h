#pragma once
#include "TObject.h"

#pragma warning(disable:4005)

class S_Character :public TObject
{
public:
	T_STR m_szName;
	TBoneObj* m_pBoneObject;
	int m_iStarFrame;
	int m_iLastFrame;
	int m_iCurrentFrame;
	float m_fFrame;
	float m_fLerpTime;
	D3DXMATRIX m_pMatrix[255];
	int m_iMatrixIndex;
	ID3D11Buffer* m_pBoneBuffer;
	ID3D11ShaderResourceView* m_pBoneBufferRV;
public:
	bool Init();
	bool Frame();
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();
	bool Add(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext*    pImmediateContext,
		const TCHAR* strSkinFileName,
		const TCHAR* strSkinShaderName,
		int		iMatrixIndex = -1,
		int		iModelMatrixIndex = -1);

	void		SetModelMaterixID(int iMatrixIndex);
	void		SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	void		SetActionFrame(int iStart, int iEnd,
		int iCharacterMatrixIndex = -1,
		int iModelMatrixIndex = -1);
public:
	S_Character(void);
	virtual ~S_Character(void);
};

