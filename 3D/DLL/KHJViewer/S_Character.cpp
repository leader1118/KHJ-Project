#include "S_Character.h"
#include "xTimer.h"
#include "TObjMgr.h"

void S_Character::SetActionFrame(int iStart, int iEnd,
	int iCharacterMatrixIndex,
	int iModelMatrixIndex)
{
	m_iStartFrame = iStart;
	m_iLastFrame = iEnd;
	m_iCurrentFrame = (float)iStart;
	m_fFrame = m_iStartFrame;

	if (iCharacterMatrixIndex >= 0)
	{
		m_iMatrixIndex = iCharacterMatrixIndex;
	}
	if (iModelMatrixIndex >= 0)
	{
		SetModelMaterixID(iModelMatrixIndex);
	}
}

void S_Character::SetModelMaterixID(int iMatrixIndex)
{
	for (int iObj = 0; iObj < m_pModelList.size(); iObj++)
	{
		m_pSubObjList[iObj]->SetMatrixIndex(iMatrixIndex);
	}
}

bool S_Character::Add(ID3D11Device* pd3dDevice, ID3D11DeviceContext* plmmediateContext,
	const TCHAR* strSkinFileName,
	const TCHAR* strSkinShaderName,
	int iMatrixIndex,
	int iModelMatrixIndex)
{
	if (!_tcsicmp(strSkinFileName, _T("null")))
	{
		return false;
	}
	if (!Load(pd3dDevice, strSkinFileName, strSkinShaderName))
	{
		return false;
	}
	m_pBoneObject = (TBoneObj*)I_ObjMgr.GetPtr(iMatrixIndex);

	SetActionFrame(m_pBoneObject->m_Scene.iFirstFrame,
		m_pBoneObject->m_Scene.iLastFrame,
		iMatrixIndex, iModelMatrixIndex);
	return true;
}

bool S_Character::Init()
{
	TObject::Init();
	return true;
}

bool S_Character::Render(ID3D11DeviceContext* pContext)
{
	m_pBoneObject->m_pMatrix = m_pMatrix;

	TObject::Render(pContext);

	m_pBoneObject->Render(pContext);
	return true;
}

void S_Character::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	TObject::SetMatrix(pWorld, pView, pProj);
	m_pBoneObject->SetMatrix(pWorld, pView, pProj);
}

bool S_Character::Release()
{
	TObject::Release();
	return true;
}

bool S_Character::Frame()
{
	_ASSERT(m_pBoneObject);

	m_fFrame += (g_fSecPerFrame* m_pBoneObject->m_Scene.iFrameSpeed);
	m_iCurrentFrame = (int)m_fFrame;

	m_fLerpTime = m_fFrame - m_iCurrentFrame;
	if (m_pBoneObject->AniFrame(m_iCurrentFrame, m_fLerpTime, m_iStartFrame, m_iLastFrame, m_pMatrix))
	{
		m_iCurrentFrame = m_iStartFrame;
		m_fFrame = (float)m_iStartFrame;
	}
	TObject::Frame();
	return true;
}
S_Character::S_Character()
{
	m_iMatrixIndex = -1;
}


S_Character::~S_Character()
{
}
