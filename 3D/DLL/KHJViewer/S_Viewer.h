#pragma once
#include "xCore.h"
#include "S_HeroObj.h"
class S_Viewer : public xCore
{
public:
	shared_ptr<xCamera> m_pMainCamera;
	D3DXMATRIX m_matWorld;
	vector<shared_ptr<S_HeroObj>> m_HeroObj;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	int WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HRESULT CreateResource();
	HRESULT DeleteResource();
public:
	S_Viewer(void);
	virtual ~S_Viewer(void);
};

