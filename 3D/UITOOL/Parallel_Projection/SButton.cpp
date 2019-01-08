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
}

SButton::SButton()
{
}


SButton::~SButton()
{
}
