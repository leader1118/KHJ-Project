#include "TCore.h"
HDC		g_hScreenDC;
HDC		g_hOffScreenDC;
bool TCore::GameInit()
{
	m_Timer.Init();
	I_Input.Init();
	// �� 1�� ���� �������
	m_hScreenDC = GetDC(m_hWnd);
	// �� 2�� ���۸� �����Ѵ�.
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);// �޸�
	m_hOffScreenBitmap = CreateCompatibleBitmap(
		m_hScreenDC,
		m_rtClient.right,
		m_rtClient.bottom );
	// ��ȯ�� = ���� ���õǾ� �ִ� ��Ʈ��
	m_hOldBitmap = (HBITMAP)SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);
	
	g_hScreenDC = m_hScreenDC;
	g_hOffScreenDC = m_hOffScreenDC;

	// m_hOffScreenDC �� �����.
	COLORREF bkColor = RGB(255, 255, 255);
	m_hbrBack = CreateSolidBrush(bkColor);
	m_hbrOld = 
		(HBRUSH)SelectObject(m_hOffScreenDC, m_hbrBack);

	m_hPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	m_hOldPen = (HPEN)SelectObject(m_hOffScreenDC, m_hPen);

	// ��Ʈ
	m_fontDefault = CreateFont( 20, 0, 0, FW_BOLD, 
		0,0,0,0,
		HANGEUL_CHARSET, 3,2,1, 
		VARIABLE_PITCH | FF_ROMAN, 
		_T("���"));
	m_fontDefaultOld = (HFONT)SelectObject(m_hOffScreenDC, m_fontDefault);
	Init();
	return true;
}
bool TCore::GameRelease()
{
	Release();
	SelectObject(m_hOffScreenDC, m_hOldPen);
	DeleteObject(m_hPen);
	SelectObject(m_hOffScreenDC, m_hbrOld);
	DeleteObject(m_hbrBack);
	SelectObject(m_hOffScreenDC, m_hOldBitmap);
	SelectObject(m_hOffScreenDC, m_fontDefaultOld);
	DeleteObject(m_fontDefault);
	// GetDC()�� ���� DC�� ReleaseDC�� �����Ѵ�.
	ReleaseDC(m_hWnd, m_hScreenDC);
	m_Timer.Release();
	I_Input.Release();
	return true;
}
bool TCore::GameFrame()
{
	m_Timer.Frame();
	I_Input.Frame();
	PreFrame();
		Frame();
	PostFrame();
	return true;
}
bool TCore::PreRender()
{
	SelectObject(m_hOffScreenDC, m_hbrBack);
	PatBlt(m_hOffScreenDC, 0, 0,
		m_rtClient.right, m_rtClient.bottom,
		PATCOPY);		
	return true;
}
bool TCore::PostRender()
{
	// m_hOffScreenDC �̹����� m_hScreenDC�� �����ض�.
	BitBlt(m_hScreenDC, m_rtClient.left, m_rtClient.top,
		m_rtClient.right, m_rtClient.bottom,
		m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}
bool TCore::DrawDebug(TCHAR* pString, int iX, int iY)
{	
	if (m_hOffScreenDC != NULL)
	{
		SetBkColor(m_hOffScreenDC, RGB(255, 0, 0));
		SetTextColor(m_hOffScreenDC, RGB(0, 0, 255));
		SetBkMode(m_hOffScreenDC, TRANSPARENT);
		SetTextAlign(m_hOffScreenDC, TA_LEFT);

		TextOut(m_hOffScreenDC, iX, iY, pString, wcslen(pString));
	}
	return true;
}
bool TCore::DrawDebug()
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
	}
	return true;
}
bool TCore::GameRender()
{
	PreRender();
		Render();
		m_Timer.Render();	
		I_Input.Render();
		DrawDebug();
	PostRender();
	return true;
}
bool TCore::GameRun()
{
	GameFrame();
	GameRender();
	return true;
};
void TCore::MsgEvent(MSG msg)
{
	I_Input.MsgEvent(msg);
};
bool	TCore::ResizeClient(UINT iWidth, UINT iHeight)
{
	TWindow::ResizeClient(iWidth, iHeight);
	if (m_hScreenDC == NULL || m_hOffScreenDC == NULL) return true;
	// ���������� �ݵ�� ����� ���¸� �����ϰ� �����ؾ� �Ѵ�.
	SelectObject(m_hOffScreenDC, m_hOldBitmap);
	DeleteObject(m_hOffScreenBitmap);

	m_hOffScreenBitmap = CreateCompatibleBitmap(
		m_hScreenDC,
		m_rtClient.right,
		m_rtClient.bottom);
	// ��ȯ�� = ���� ���õǾ� �ִ� ��Ʈ��
	m_hOldBitmap = (HBITMAP)SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);
	return true;
}
TCore::TCore()
{
}


TCore::~TCore()
{
}
