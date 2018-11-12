#include "CCCore.h"

bool	CCCore::GameInit()
{
	m_Timer.Init();
	m_Input.Init();
	// �� 1�� ���� �������
	m_hScreenDC = GetDC(m_hWnd);
	// �� 2�� ���۸� �����Ѵ�.
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC); //�޸�
	m_hOffScreenBitmap = CreateCompatibleBitmap(
		m_hScreenDC,
		m_rtClient.right,
		m_rtClient.bottom);
	// ��ȯ�� = ���� ���õǾ� �ִ� ��Ʈ��
	m_hOldBitmap = (HBITMAP)SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);
	
	Init();
	return true;
}

bool	CCCore::GameRelease()
{
	Release();
	SelectObject(m_hOffScreenDC, m_hOldBitmap);
	ReleaseDC(m_hWnd, m_hScreenDC);
	m_Timer.Release();
	m_Input.Release();
	return true;
}
bool	CCCore::GameFrame()
{
	m_Timer.Frame();
	m_Input.Frame();
	Frame();

	return true;
}
bool CCCore::PreRender()
{
	// m_hOffScreenDC�� �����.
	COLORREF bkColor = RGB(255, 255, 255);
	HBRUSH hbrBack = CreateSolidBrush(bkColor);
	SelectObject(m_hOffScreenDC, hbrBack);
	PatBlt(m_hOffScreenDC, 0, 0,
		m_rtClient.right, m_rtClient.bottom,
		PATCOPY);
	return true;
}

bool CCCore::PostRender()
{
	// m_hOffScreenDC �̹����� m_hScreenDC�� �����ض�.
	BitBlt(m_hScreenDC, m_rtClient.left, m_rtClient.top,
		m_rtClient.right, m_rtClient.bottom,
		m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}
bool	CCCore::DrawDebug()
{
	RECT rect;
	if (m_hOffScreenDC != NULL)
	{
		GetClientRect(m_hWnd, &rect);
		SetBkColor(m_hOffScreenDC, RGB(255, 0, 0));
		SetTextColor(m_hOffScreenDC, RGB(0, 0, 255));
		SetBkMode(m_hOffScreenDC, TRANSPARENT);
		// �׸���
		DrawText(m_hOffScreenDC, m_Timer.m_csBuffer, -1,
			&rect, DT_LEFT | DT_VCENTER);
		//SetTextAlign(hdc,TA_LEFT);
		//TextOut(hdc,100,100,L"KHJ",
		//wcslen(L"KHJ"));
	}
	return true;
}
bool	CCCore::GameRender()
{
	PreRender();
	Render();
	m_Timer.Render();
	m_Input.Render();
	DrawDebug();
	PostRender();
	return true;
}
bool CCCore::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}
void CCCore::MsgEvent(MSG msg)
{
	m_Input.MsgEvent(msg);
}
CCCore::CCCore()
{
}


CCCore::~CCCore()
{
}
