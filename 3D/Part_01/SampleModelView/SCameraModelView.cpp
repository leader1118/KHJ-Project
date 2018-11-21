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
	//xCamera::Update();
	return true;
}

SCameraModelView::SCameraModelView()
{
}


SCameraModelView::~SCameraModelView()
{
}
