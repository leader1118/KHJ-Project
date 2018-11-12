#include "CCTimer.h"

int			g_iFPS;// 1�ʴ� ������ ����
float		g_fSecPerFrame; //1�������� ����ð�
float		g_fAccumulation; // ����� ��� �ð�
// Ŭ���� ��� ���� �ʱ�ȭ

bool		CCTimer::Init()
{
	m_dwBeforeTick = timeGetTime();
	ZeroMemory(m_csBuffer, sizeof(TCHAR)*MAX_PATH);
	return true;
};
// �� �����ӿ��� ����� ����Ѵ�.
bool		CCTimer::Frame()
{
	//1000==1�� (winmm.lib)
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;

	g_fSecPerFrame = m_fSecondPerFrame = dwElapseTick / 1000.0f;
	g_fAccumulation = m_fAccumulation += m_fSecondPerFrame;
	m_fFrameTime += m_fSecondPerFrame;

	if (m_fFrameTime > 1.0f)
	{
		g_iFPS = m_iFPS = m_dwFrameCnt;
		m_dwFrameCnt = 0;
		m_fFrameTime -= 1.0f;
		// _CRT_SECURE_NO_WARNINGS
		//_stprintf_s(m_csBuffer,L"Timer:[%10.4f]FPS:[%d] %f\n",
		// m_fAccumulation,m_iFPS,m_fSecondPerFrame);
		//OutputDebugString(m_csBuffer);
	}

	m_dwFrameCnt++;
	m_dwBeforeTick = dwCurrentTick;
	return true;
}
// �� �����ӿ��� ��ο츦 ����Ѵ�.
bool		CCTimer::Render()
{
	_stprintf_s(m_csBuffer, L"Timer:[%10.4f] FPS:[%d] %10.4f\n",
		m_fAccumulation, m_iFPS, m_fSecondPerFrame);
	//OutputDebugString
	return true;
}
bool		CCTimer::Release()
{
	return true;
}

CCTimer::CCTimer()
{
	m_iFPS = 0;//1�ʴ� ������ ����
	m_dwFrameCnt = 0;
	m_fSecondPerFrame = 0.0f; // 1�������� ��� �ð�
	m_fAccumulation = 0.0f; // ����� ��� �ð�
	m_fFrameTime = 0.0f;
}


CCTimer::~CCTimer()
{
}
