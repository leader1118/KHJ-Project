#pragma once
#include "Std.h"
enum KeyState
{
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD,
};
class InPut : public Singleton<InPut>
{
	friend class Singleton<InPut>;
	DWORD	KeyCheck(DWORD dwKey);
	DWORD  m_dwKeyState[256];
	DWORD  m_dwBeforeMouseState[3];
public:
	DWORD  m_dwMouseState[3];
	POINT  m_MousePos;
public:
	DWORD   Key(DWORD dwKey);
	void	MsgEvent(MSG msg);
	bool	Init();		// �ʱ�ȭ
	bool	Frame();	// ���
	bool	Render();	// ��ο�
	bool	Release();	// �Ҹ�, ����
protected:
	InPut();
	virtual ~InPut();
};
#define I_Input InPut::GetInstance()
