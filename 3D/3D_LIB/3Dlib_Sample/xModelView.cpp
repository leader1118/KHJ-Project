#include "xModelView.h"

LRESULT	xModelView::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_LBUTTONDOWN)
	{
		short iMouseX = LOWORD(lParam);
		short iMouseY = HIWORD(lParam);
		m_WorldArcBall.OnBegin(iMouseX, iMouseY);
	}
	if (msg == WM_RBUTTONDOWN)
	{

	}
	if (msg == WM_MOUSEMOVE)
	{
		short iMouseX = LOWORD(lParam);
		short iMouseY = HIWORD(lParam);
		m_WorldArcBall.OnMove(iMouseX, iMouseY);
	}
	if (msg == WM_LBUTTONUP)
	{
		m_WorldArcBall.OnEnd();
	}
	if (msg == WM_RBUTTONUP)
	{

	}
	return 1;
}
bool xModelView::Update(D3DXVECTOR4 vValue)
{
	xCamera::Update(vValue);
	D3DXMATRIX mModelRot, mModelLastRotInv, mInvView;

	D3DXMatrixInverse(&mInvView, NULL, &m_matView);
	mInvView._41 = 0.0f;
	mInvView._42 = 0.0f;
	mInvView._43 = 0.0f;
	D3DXMatrixInverse(&mModelLastRotInv,NULL, &m_mModelLastRot);
	 
	mModelRot = m_WorldArcBall.GetRotationMatrix();
	m_mModelRot = m_mModelRot * m_matView * mModelLastRotInv * mModelRot * mInvView;

	m_mModelLastRot = mModelRot;

	m_mModelRot._41 = 0;
	m_mModelRot._42 = 0;
	m_mModelRot._43 = 0;	
	m_matWorld = m_mModelRot;
	return true;
}

xModelView::xModelView()
{	
	D3DXMatrixIdentity(&m_mModelRot);
	D3DXMatrixIdentity(&m_mModelLastRot);	
}


xModelView::~xModelView()
{
}
