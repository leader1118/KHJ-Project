#pragma once
#include "S_Std.h"

class S_Input :public Singleton<S_Input>
{
private:
	friend class Singleton<S_Input>;
public:
	bool m_bKeydown[MAX_ARRAY];
	bool m_bKeyUp[MAX_ARRAY];
public:
	POINT m_ptMousePos;
	bool StayKeydown(INT iKey);
	bool OnceKeydwon(INT iKey);
	bool OnceKeyUp(INT iKey);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	S_Input();
	virtual ~S_Input();
};
#define S_INPUT S_Input::GetInstance()

