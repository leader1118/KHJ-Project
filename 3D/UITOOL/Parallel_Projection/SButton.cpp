#include "SButton.h"

D3DXVECTOR3 SButton::Gen(float x, float y)
{
	D3DXVECTOR3 vRet = SActor::Gen(x, y);
	//vRet.x = vRet.x * (800 * 0.5f);
	//vRet.y = vRet.y * (600 * 0.5f);
	return vRet;
}

void SButton::SetVertexData()
{
	m_cpPoint[0] = { m_rtInit.left*1.0f,m_rtInit.top*1.0f };
	m_cpPoint[1] = { m_rtInit.left + m_rtInit.right*m_sOffset.fScaleX0,m_rtInit.top*1.0f };
	m_cpPoint[2] = { m_rtInit.left + m_rtInit.right*(1.0f - m_sOffset.fScaleX1),m_rtInit.top*1.0f };
	m_cpPoint[3] = { m_rtInit.left + m_rtInit.right*1.0f,m_rtInit.left*1.0f };

	m_cpPoint[4] = { m_cpPoint[0].x,m_rtInit.top + m_rtInit.bottom*m_sOffset.fScaleY0 };
	m_cpPoint[5] = { m_cpPoint[1].x,m_rtInit.top + m_rtInit.bottom*m_sOffset.fScaleY0 };
	m_cpPoint[6] = { m_cpPoint[2].x,m_rtInit.top + m_rtInit.bottom*m_sOffset.fScaleY0 };
	m_cpPoint[7] = { m_cpPoint[3].x,m_rtInit.top + m_rtInit.bottom*m_sOffset.fScaleY0 };

	m_cpPoint[8] = { m_cpPoint[0].x,m_rtInit.top + m_rtInit.bottom * (1.0f - m_sOffset.fScaleY1) };
	m_cpPoint[9] = { m_cpPoint[1].x,m_rtInit.top + m_rtInit.bottom*(1.0f - m_sOffset.fScaleY1) };
	m_cpPoint[10] = { m_cpPoint[2].x,m_rtInit.top + m_rtInit.bottom * (1.0f - m_sOffset.fScaleY1) };
	m_cpPoint[11] = { m_cpPoint[3].x,m_rtInit.top + m_rtInit.bottom*(1.0f - m_sOffset.fScaleY1) };

	m_cpPoint[12] = { m_cpPoint[0].x,m_rtInit.top + m_rtInit.bottom*1.0f };
	m_cpPoint[13] = { m_cpPoint[1].x,m_rtInit.top + m_rtInit.bottom*1.0f };
	m_cpPoint[14] = { m_cpPoint[2].x,m_rtInit.top + m_rtInit.bottom*1.0f };
	m_cpPoint[15] = { m_cpPoint[3].x,m_rtInit.top + m_rtInit.bottom*1.0f };

	m_Actor[0].Setdata(m_cpPoint[0].x, m_cpPoint[0].y, m_cpPoint[1].x - m_cpPoint[0].x, m_cpPoint[4].y - m_cpPoint[0].y);
	m_Actor[0].m_VertexList[1].t.x = m_sOffset.fOffsetU0;
	m_Actor[0].m_VertexList[1].t.y = 0.0f;
	m_Actor[0].m_VertexList[2].t.x = 0.0f;
	m_Actor[0].m_VertexList[2].t.y = m_sOffset.fOffsetV0;
	m_Actor[0].m_VertexList[3] = m_Actor[0].m_VertexList[2];
	m_Actor[0].m_VertexList[4] = m_Actor[0].m_VertexList[1];
	m_Actor[0].m_VertexList[5].t.x = m_sOffset.fOffsetU0;
	m_Actor[0].m_VertexList[5].t.y = m_sOffset.fOffsetV0;

	m_Actor[1].Setdata(m_cpPoint[1].x, m_cpPoint[1].y, m_cpPoint[2].x - m_cpPoint[1].x, m_cpPoint[6].y - m_cpPoint[2].y);
	m_Actor[1].m_VertexList[0].t.x = m_sOffset.fOffsetU0;
	m_Actor[1].m_VertexList[0].t.y = 0.0f;
	m_Actor[1].m_VertexList[1].t.x = 1.0f - m_sOffset.fOffsetU0;
	m_Actor[1].m_VertexList[1].t.y = 0.0f;
	m_Actor[1].m_VertexList[2].t.x = m_Actor[1].m_VertexList[0].t.x;
	m_Actor[1].m_VertexList[2].t.y = m_sOffset.fOffsetV0;
	m_Actor[1].m_VertexList[3] = m_Actor[1].m_VertexList[2];
	m_Actor[1].m_VertexList[4] = m_Actor[1].m_VertexList[1];
	m_Actor[1].m_VertexList[5].t.x = m_Actor[1].m_VertexList[1].t.x;
	m_Actor[1].m_VertexList[5].t.y = m_Actor[1].m_VertexList[2].t.y;

	m_Actor[2].Setdata(m_cpPoint[2].x, m_cpPoint[2].y, m_cpPoint[3].x - m_cpPoint[2].x, m_cpPoint[6].y - m_cpPoint[2].y);
	m_Actor[2].m_VertexList[0].t.x = 1.0f - m_sOffset.fOffsetU0;
	m_Actor[2].m_VertexList[0].t.y = 0.0f;
	m_Actor[2].m_VertexList[1].t.x = 1.0f;
	m_Actor[2].m_VertexList[1].t.y = 0.0f;
	m_Actor[2].m_VertexList[2].t.x = m_Actor[2].m_VertexList[0].t.x;
	m_Actor[2].m_VertexList[2].t.y = m_sOffset.fOffsetV0;
	m_Actor[2].m_VertexList[3] = m_Actor[2].m_VertexList[2];
	m_Actor[2].m_VertexList[4] = m_Actor[2].m_VertexList[1];
	m_Actor[2].m_VertexList[5].t.x = m_Actor[2].m_VertexList[1].t.x;
	m_Actor[2].m_VertexList[5].t.y = m_Actor[2].m_VertexList[2].t.y;

#pragma endregion
	////////
#pragma region 3~5
	m_Actor[3].Setdata(m_cpPoint[4].x, m_cpPoint[4].y, m_cpPoint[1].x - m_cpPoint[0].x, m_cpPoint[8].y - m_cpPoint[4].y);
	m_Actor[3].m_VertexList[0].t = m_Actor[0].m_VertexList[2].t;
	m_Actor[3].m_VertexList[1].t = m_Actor[0].m_VertexList[5].t;
	m_Actor[3].m_VertexList[2].t.x = 0.0f;
	m_Actor[3].m_VertexList[2].t.y = 1.0f - (m_sOffset.fOffsetV0 - m_sOffset.fOffsetV1);
	m_Actor[3].m_VertexList[3] = m_Actor[3].m_VertexList[2];
	m_Actor[3].m_VertexList[4] = m_Actor[3].m_VertexList[1];
	m_Actor[3].m_VertexList[5].t.x = m_Actor[3].m_VertexList[1].t.x;
	m_Actor[3].m_VertexList[5].t.y = m_Actor[3].m_VertexList[2].t.y;

	m_Actor[4].Setdata(m_cpPoint[5].x, m_cpPoint[5].y, m_cpPoint[2].x - m_cpPoint[1].x, m_cpPoint[8].y - m_cpPoint[4].y);
	m_Actor[4].m_VertexList[0].t = m_Actor[3].m_VertexList[1].t;
	m_Actor[4].m_VertexList[1].t.x = m_Actor[1].m_VertexList[1].t.x;
	m_Actor[4].m_VertexList[1].t.y = m_sOffset.fOffsetV0;
	m_Actor[4].m_VertexList[2].t.x = m_sOffset.fOffsetU0;
	m_Actor[4].m_VertexList[2].t.y = 1.0f - (m_sOffset.fOffsetV0 - m_sOffset.fOffsetV1);
	m_Actor[4].m_VertexList[3] = m_Actor[4].m_VertexList[2];
	m_Actor[4].m_VertexList[4] = m_Actor[4].m_VertexList[1];
	m_Actor[4].m_VertexList[5].t.x = m_Actor[4].m_VertexList[1].t.x;
	m_Actor[4].m_VertexList[5].t.y = m_Actor[4].m_VertexList[2].t.y;

	m_Actor[5].Setdata(m_cpPoint[6].x, m_cpPoint[6].y, m_cpPoint[3].x - m_cpPoint[2].x, m_cpPoint[8].y - m_cpPoint[4].y);
	m_Actor[5].m_VertexList[0].t = m_Actor[4].m_VertexList[1].t;
	m_Actor[5].m_VertexList[1].t.x = 1.0f;
	m_Actor[5].m_VertexList[1].t.y = m_sOffset.fOffsetV0;
	m_Actor[5].m_VertexList[2].t = m_Actor[4].m_VertexList[5].t;
	m_Actor[5].m_VertexList[3] = m_Actor[5].m_VertexList[2];
	m_Actor[5].m_VertexList[4] = m_Actor[5].m_VertexList[1];
	m_Actor[5].m_VertexList[5].t.x = m_Actor[5].m_VertexList[1].t.x;
	m_Actor[5].m_VertexList[5].t.y = m_Actor[5].m_VertexList[2].t.y;
#pragma endregion 3~5

#pragma region 6~9
	m_Actor[6].Setdata(m_cpPoint[8].x, m_cpPoint[8].y, m_cpPoint[1].x - m_cpPoint[0].y, m_cpPoint[12].y - m_cpPoint[8].y);
	m_Actor[6].m_VertexList[0].t = m_Actor[3].m_VertexList[2].t;
	m_Actor[6].m_VertexList[1].t = m_Actor[3].m_VertexList[5].t;
	m_Actor[6].m_VertexList[2].t.x = 0.0f;
	m_Actor[6].m_VertexList[2].t.y = 1.0f;
	m_Actor[6].m_VertexList[3] = m_Actor[6].m_VertexList[2];
	m_Actor[6].m_VertexList[4] = m_Actor[6].m_VertexList[1];
	m_Actor[6].m_VertexList[5].t.x = m_Actor[6].m_VertexList[1].t.x;
	m_Actor[6].m_VertexList[5].t.y = m_Actor[6].m_VertexList[2].t.y;

	m_Actor[7].Setdata(m_cpPoint[9].x, m_cpPoint[9].y, m_cpPoint[2].x - m_cpPoint[1].x, m_cpPoint[12].y - m_cpPoint[8].y);
	m_Actor[7].m_VertexList[0].t = m_Actor[4].m_VertexList[3].t;
	m_Actor[7].m_VertexList[1].t = m_Actor[4].m_VertexList[5].t;
	m_Actor[7].m_VertexList[2].t.x = m_sOffset.fOffsetU0;
	m_Actor[7].m_VertexList[2].t.y = 1.0f;
	m_Actor[7].m_VertexList[3] = m_Actor[7].m_VertexList[2];
	m_Actor[7].m_VertexList[4] = m_Actor[7].m_VertexList[1];
	m_Actor[7].m_VertexList[5].t.x = m_Actor[7].m_VertexList[1].t.x;
	m_Actor[7].m_VertexList[5].t.y = m_Actor[7].m_VertexList[2].t.y;

	m_Actor[8].Setdata(m_cpPoint[10].x, m_cpPoint[10].y, m_cpPoint[3].x - m_cpPoint[2].x, m_cpPoint[12].y - m_cpPoint[8].y);
	m_Actor[8].m_VertexList[0].t = m_Actor[5].m_VertexList[3].t;
	m_Actor[8].m_VertexList[1].t = m_Actor[5].m_VertexList[5].t;
	m_Actor[8].m_VertexList[2].t = m_Actor[7].m_VertexList[5].t;
	m_Actor[8].m_VertexList[3] = m_Actor[8].m_VertexList[2];
	m_Actor[8].m_VertexList[4] = m_Actor[8].m_VertexList[1];
	m_Actor[8].m_VertexList[5].t.x = m_Actor[8].m_VertexList[1].t.x;
	m_Actor[8].m_VertexList[5].t.y = m_Actor[8].m_VertexList[2].t.y;
	//////////////////////
#pragma endregion 3~5

	for (int iRect = 0; iRect < 9; iRect++)
	{
		for (int iV = 0; iV < 6; iV++)
		{
			m_tVertexList.push_back(m_Actor[iRect].m_VertexList[iV]);
		}
	}
}

void SButton::MoveX(float fDis)
{
	for (int iV = 0; iV < 6; iV++)
	{
		m_VertexList[iV].p.x += fDis;
	}
	GenCenter();
}

void SButton::MoveY(float fDis)
{
	for (int iV = 0; iV < 6; iV++)
	{
		m_VertexList[iV].p.y += fDis;
	}
	GenCenter();
}


bool SButton::SetData(RECT rt,float fScaleX0, float fScaleX1,
	float fScaleY0, float fScaleY1,
	float fOffsetU0, float fOffsetU1,
	float fOffsetV0, float fOffsetV1)
{
	m_rtInit = rt;
	m_sOffset.fScaleX0 = fScaleX0;
	m_sOffset.fScaleX1 = fScaleX1;
	m_sOffset.fScaleY0 = fScaleY0;
	m_sOffset.fScaleY1 = fScaleY1;
	
	m_sOffset.fOffsetU0 = fOffsetU0;
	m_sOffset.fOffsetU1 = fOffsetU1;
	m_sOffset.fOffsetV0 = fOffsetV1;
	m_sOffset.fOffsetV0 = fOffsetV1;
	SetVertexData();
	return true;
}

bool SButton::Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile)
{
	LoadVertexShaderFile(pd3dDevice,pVsFile);
	LoadPixelShaderFile(pd3dDevice,pPsFile);
	CreateInputLayout(pd3dDevice);
	
	CreateVertexBuffer(pd3dDevice, &m_tVertexList.at(0), m_tVertexList.size());
	CreateConstantBuffer(pd3dDevice,
		&m_ActorCB,
		sizeof(SActorCB));
	
	CreateLayout(pd3dDevice, m_dxObj.m_pVSBlob);
	LoadTexture(pd3dDevice, pTexFile);
	return true;
}
bool SButton::Init()
{
	return true;
}

bool SButton::Frame(float fGameTimer, float fFps)
{
	m_ActorCB.m_matWorld.RoationZ(fGameTimer);
	D3DXVECTOR3 vEye = D3DXVECTOR3(0.0f, 0.0f, -50.f);
	D3DXMatrixLookAtLH((D3DXMATRIX*)&m_ActorCB.m_matView, &vEye,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	D3DXMatrixOrthoLH((D3DXMATRIX*)&m_ActorCB.m_matProj, 2, 2, 0.0f, 100.0f);

	m_ActorCB.m_matWorld.Transpose();
	m_ActorCB.m_matView.Transpose();
	m_ActorCB.m_matProj.Transpose();
	return true;
}

bool SButton::Render(ID3D11DeviceContext* pContext, UINT iVertexSize)
{
	
	pContext->UpdateSubresource(m_dxObj.m_pConstantBuffer.Get(), 0, NULL, &m_ActorCB, 0, 0);
	m_dxObj.PreRender(pContext,iVertexSize);
	PostRender(pContext);
	return true;
}
bool SButton::PostRender(ID3D11DeviceContext* pContext)
{
	pContext->Draw(m_tVertexList.size(), 0);
	return true;
}
bool SButton::Release()
{
	SActor::Release();
	for (int iRect = 0; iRect < 9; iRect++)
	{
		m_Actor[iRect].Release();
	}
	return true;
}
SButton::SButton()
{
}


SButton::~SButton()
{
}
