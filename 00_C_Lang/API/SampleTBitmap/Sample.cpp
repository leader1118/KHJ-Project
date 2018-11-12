#include "TCore.h"
#include "TBitmap.h"
struct tPoint
{
	float x, y;
};
class Sample : public TCore
{
	TBitmap  m_bitmap;
	tPoint  m_pos;
public:
	bool	Init()
	{
		m_pos.x = 100;
		m_pos.y = 100;
		m_bitmap.Load(L"rogo1.bmp.bmp");
		return true;
	}
	bool	Frame()
	{
		if (I_Input.Key('W'))
		{
			m_pos.y += -1 * g_fSecPerFrame*300.0f;
		}
		if (I_Input.Key('S'))
		{
			m_pos.y += 1 * g_fSecPerFrame*300.0f;
		}
		if (I_Input.Key('A'))
		{
			m_pos.x += -1 * g_fSecPerFrame*300.0f;
		}
		if (I_Input.Key('D'))
		{
			m_pos.x += 1 * g_fSecPerFrame*300.0f;
		}
		return true;
	}
	bool	Render() {
		BitBlt(m_hOffScreenDC, m_pos.x, m_pos.y, 800, 600,
			m_bitmap.m_hMemDC, 0, 0, SRCCOPY);


		return true;
	}
	bool	Release() {

		return true;
	}
public:
	Sample() {}
	~Sample() {}
};
GAME_RUN("SampleInput", 800, 600)