#pragma once
#include "DIWindow.h"
#include "DTimer.h"
#include "DDirectWrite.h"
#include "DIDInput.h"

class Sample : public DIWindow
{
public:
	DTimer				m_Timer;
	DDirectWrite		m_Font;
	T_STR				m_strBuffer;
	D2D1_MATRIX_3X2_F	m_matWorld;
	float				m_fScale;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	Sample(void);
	~Sample(void);

};