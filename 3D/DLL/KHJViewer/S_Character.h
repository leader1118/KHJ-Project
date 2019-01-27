#pragma once
#include "xstd.h"
class S_Character
{
public:   
	T_STR m_szName;
	int m_iStartFrame;
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
	bool 
public:
	S_Character();
	virtual ~S_Character();
};

