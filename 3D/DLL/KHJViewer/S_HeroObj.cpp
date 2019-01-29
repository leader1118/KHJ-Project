#include "S_HeroObj.h"


inline void DXUT_SetDebugName(ID3D11DeviceChild* pObj, const CHAR* pstrName)
{
	if (pObj)
		pObj->SetPrivateData(WKPDID_D3DDebugObjectName, lstrlenA(pstrName), pstrName);
}
HRESULT S_HeroObj::CreateConstantBuffer()
{
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC Desc;
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.MiscFlags = 0;
	Desc.ByteWidth = sizeof(CBConstBoneWorld);
	V_RETURN(g_pd3dDevice->CreateBuffer(&Desc, NULL, m_pCBConstBoneWorld.GetAddressOf()));
	DXUT_SetDebugName(m_pCBConstBoneWorld.Get(), "CBConstBoneWorld");
	return hr;
}

void S_HeroObj::SetActionFrame(int iStart, int iEnd, int iCharacterMatrixIndex, int iModelMatrixIndex)
{
	m_iStartFrame = iStart;
	m_iLastFrame = iEnd;
	m_iCurrentFrame = (float)iStart;
	m_fFrame = m_iStartFrame;

	if (iCharacterMatrixIndex >= 0)
	{
		m_iMatrixIndex = iCharacterMatrixIndex;
	}
}


void S_HeroObj::SetBoneMatrices(vector<D3DXMATRIX>* pList)
{
	for (UINT i = 0; i < pList->size(); i++)
	{
		D3DXMatrixTranspose(&m_cbBoneData.g_mConstBoneWorld[i], &((*pList)[i] * m_pMatrix[i]));
	}
}

bool S_HeroObj::Frame()
{
	m_fFrame += (g_fSecPerFrame* m_fSpeed* m_pBoneObject->m_Scene.iFrameSpeed);
	m_iCurrentFrame = (int)m_fFrame;

	m_fLerpTime = m_fFrame - m_iCurrentFrame;
#ifdef _DEBUG
	TCHAR  strMessage[MAX_PATH] = { 0, };
	_stprintf_s(strMessage, _T("<===== %d [%10.4f] %d====>\n "), m_iCurrentFrame, m_fLerpTime, m_iCurrentFrame + 1);
	OutputDebugString(strMessage);
#endif
	if (m_pBoneObject->AniFrame(m_fFrame,
		m_fLerpTime,
		m_iStartFrame,
		m_iLastFrame,
		m_pMatrix))
	{
		m_iCurrentFrame = m_iStartFrame;
		m_fFrame = (float)m_iStartFrame + m_fLerpTime;
	}

	return true;
}

bool S_HeroObj::Render(ID3D11DeviceContext* pContext)
{
	for (int iObj = 0; iObj < m_pChar->m_pModelList.size(); iObj++)
	{
		TSkinObj* pModel = (TSkinObj*)m_pChar->m_pModelList[iObj]->m_pModel;
		_ASSERT(pModel);
		pModel->SetMatrix(&m_matWorld, &m_matView, &m_matProj);

		if (m_bConstantBufferType)
		{
			SetBoneMatrices(pModel->GetMatrix());
			D3D11_MAPPED_SUBRESOURCE Mappedresource;
			pContext->Map(m_pCBConstBoneWorld.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Mappedresource);
			memcpy(Mappedresource.pData, &m_cbBoneData, sizeof(CBConstBoneWorld));
			pContext->Unmap(m_pCBConstBoneWorld.Get(), 0);
			pContext->VSSetConstantBuffers(1, 1, m_pCBConstBoneWorld.GetAddressOf());
		}
		else
		{
			m_pBoneObject->SetBoneMatrices(pContext, m_pMatrix, pModel->GetMatrix());

			ID3D11ShaderResourceView* aRViews[1] = { m_pBoneObject->m_pBoneBufferRV };
			pContext->VSSetShaderResources(1, 1, aRViews);
		}
		pModel->Render(pContext);
	}

	if (m_bBoneRender)
	{
		memcpy(m_pBoneObject->m_pMatrix, m_pMatrix, m_pBoneObject->m_Scene.iNumMesh * sizeof(D3DXMATRIX));
		m_pBoneObject->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
		m_pBoneObject->Render(pContext);
	}
	return true;
}
S_HeroObj::S_HeroObj()
{
	m_fSpeed = 1.0f;
	m_fFrame = 0.0f;
	m_fLerpTime = 0.0f;
	m_iStartFrame = 0;
	m_iLastFrame = 0;
	m_bConstantBufferType = false;
	m_bBoneRender = false;
}


S_HeroObj::~S_HeroObj()
{
}
