#pragma once
#include "SServerObj.h"
class SThread : public SServerObj
{
public:
	unsigned int	m_hThread; // ������ ����
	unsigned int	m_iThreadID; // ������ ID ����
	bool			m_bStarted; // �������� �������� ����
public:
	void			CreateThread(); // ������ ���� �Լ�
	virtual bool	Run(); // ������ �Լ�
	static unsigned int WINAPI HandleRunner(LPVOID parameter); // �����带 ������ �Լ�
public:
	SThread(void);
	virtual ~SThread(void);
};

