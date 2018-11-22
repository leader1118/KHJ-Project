#include "SCameraModelView.h"


LRESULT	SCameraModelView::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_LBUTTONDOWN)
	{
		short iMouseX = LOWORD(lParam);
		short iMouseY = HIWORD(lParam);
		m_WorldArcBall.OnBegin(iMouseX, iMouseY);
	}
	if (msg == WM_RBUTTONDOWN) // 카메라 회전
	{

	}
	if (msg == WM_MOUSEMOVE)
	{
		short iMouseX = LOWORD(lParam);
		short iMouseY = HIWORD(lParam);
		m_WorldArcBall.OnMove(iMouseX, iMouseY);
	}
	if (msg == WM_RBUTTONUP)
	{
		m_WorldArcBall.OnEnd();
	}
	if (msg == WM_RBUTTONUP)
	{

	}
	return 1;
}
bool SCameraModelView::Update(D3DXVECTOR4 vValue)
{
	xCamera::Update(vValue);
	D3DXMATRIX mModelRot, mModelLastRotInv, mInvView;

	D3DXMatrixInverse(&mInvView, NULL, &m_matView);
	mInvView._41 = 0.0f;
	mInvView._42 = 0.0f;
	mInvView._43 = 0.0f;
	D3DXMatrixInverse(&mModelLastRotInv, NULL, &m_mModelLastRot);

	mModelRot = m_WorldArcBall.GetRotationMatrix();
	m_mModelRot = m_mModelRot * m_matView*mModelLastRotInv*mModelRot*mInvView;

	m_mModelLastRot = m_mModelRot;
	m_mModelRot._41 = 0.0f;
	m_mModelRot._42 = 0.0f;
	m_mModelRot._43 = 0.0f;
	m_matWorld = m_mModelLastRot;
	return true;
}

SCameraModelView::SCameraModelView()
{
}


SCameraModelView::~SCameraModelView()
{
}
