#pragma once
#include "DTemplate.h"

namespace TBASIS_BASE
{

	class DIDInput : public DSingleton<DIDInput>
	{
	private:
		friend class DSingleton<DIDInput>;
	public:
		bool	Init();
		bool	Frame();
		bool	Render();
		bool	Release();
		bool	ResetDevice();
		bool	ResetResource() { return true; };
	public:
		LPDIRECTINPUT8			m_pDi;
		LPDIRECTINPUTDEVICE8	m_pDidevKey;
		LPDIRECTINPUTDEVICE8	m_pDidevMouse;
		DIDEVICEOBJECTDATA		m_didod[SAMPLE_BUFFER_SIZE];

		BYTE			m_KeyState[KEYSTATECOUNT];
		BYTE			m_KeyBeforeState[KEYSTATECOUNT];
		DIMOUSESTATE	m_MouseState;
		DIMOUSESTATE	m_MouseBeforeState;
		DWORD			m_dwElements;
		HWND			m_hWnd;
		DWORD			m_dwlmmediate;
	public:
		bool		InitDirectInput(HINSTANCE, HWND, bool, bool);
		bool		KeyProcess();
		bool		MouseProcess();
		void		DeviceAcquire();
		void		DeviceUnacquire();
		bool		IsKeyDown(DWORD dwKey);
		bool		IsKeyUP(DWORD dwKey);
		void		PostProcess();
		void		SetAcquire(bool bActive);
	public:
		DIDInput(void);
		virtual ~DIDInput(void);
	};
#define I_Input DIDInput::GetInstance()
}
using namespace TBASIS_BASE;

