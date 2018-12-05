#include "S_Core.h"

HDC		g_hScreenDC;
HDC		g_hOffScreenDC;

bool S_Core::GameInit()
{
	m_Timer.Init();
	S_INPUT.Init();
	
	m_hScreenDC = GetDC(m_hWnd);
	// �� 2�� ���۸� �����Ѵ�.
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);// �޸�
	m_hOffScreenBitmap = CreateCompatibleBitmap(
		m_hScreenDC,
		m_rtClient.right,
		m_rtClient.bottom);
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
	m_fontDefault = CreateFont(20, 0, 0, FW_BOLD,
		0, 0, 0, 0,
		HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN,
		_T("���"));
	m_fontDefaultOld = (HFONT)SelectObject(m_hOffScreenDC, m_fontDefault);
	Init();
	return true;
}

bool S_Core::GameRelease()
{
	Release();
	SelectObject(m_hOffScreenDC, m_hOldPen);
	DeleteObject(m_hPen);
	SelectObject(m_hOffScreenDC, m_hbrOld);
	DeleteObject(m_hbrBack);
	SelectObject(m_hOffScreenDC, m_hOldBitmap);
	SelectObject(m_hOffScreenDC, m_fontDefaultOld);
	DeleteObject(m_fontDefault);

	ReleaseDC(m_hWnd, m_hScreenDC);
	m_Timer.Release();
	S_INPUT.Release();
	return true;
}

bool S_Core::GameFrame()
{
	m_Timer.Frame();
	S_INPUT.Frame();
	PreFrame();
	Frame();
	PostFrame();
	return true;
}

bool S_Core::PreRender()
{
	SelectObject(m_hOffScreenDC, m_hbrBack);
	PatBlt(m_hOffScreenDC, 0, 0,
		m_rtClient.right, m_rtClient.bottom,
		PATCOPY);
	return true;
}

bool S_Core::PostRender()
{
	// m_hOffScreenDC �̹����� m_hScreenDC�� �����ض�.
	BitBlt(m_hScreenDC, m_rtClient.left, m_rtClient.top,
		m_rtClient.right, m_rtClient.bottom,
		m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}

bool S_Core::DrawDebug(TCHAR* pString, int iX, int iY)
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

bool S_Core::DrawDebug()
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
bool S_Core::GameRender()
{
	PreRender();
	Render();
	m_Timer.Render();
	S_INPUT.Render();
	DrawDebug();
	PostRender();
	return true;
}

bool S_Core::GameRun()
{
	GameFrame();
	GameRender();
	return true;
};

bool S_Core::ResizeClient(UINT iWidth, UINT iHeight)
{
	S_Window::ResizeClient(iWidth, iHeight);
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
S_Core::S_Core()
{
}


S_Core::~S_Core()
{
}
