#include "DDirectWrite.h"
#include <math.h>
#pragma comment (lib,"winmm.lib")

template <class D> inline void SafeRelease(D **ppD)
{
	if (*ppD)
	{
		(*ppD)->Release();
		*ppD = NULL;
	}
}

bool	DDirectWrite::Set(HWND hWnd, int iWidth, int iHeight, IDXGISurface1* pSurface)
{
	HRESULT hr;
	if (!Init())
	{
		return false;
	}
	m_hWnd = hWnd;

	V(CreateDeviceIndependentResources());
	V(CreateDeviceResources(pSurface));
	SetText(D2D1::Point2F(iWidth, iHeight), L"DBasisSample!", D2D1::ColorF(1, 1, 1, 1));
	return true;
}

bool DDirectWrite::Release()
{
	m_wszText.clear();
	m_wszFontFamily.clear();
	DiscardDeviceIndependentResources();
	DiscardDeviceResources();
	return true;
}
bool DDirectWrite::Init()
{
	const wchar_t defaultText[] = L"Gabriola";
	m_wszFontFamily = defaultText;
	return true;
}

DDirectWrite::DDirectWrite()
{
}


DDirectWrite::~DDirectWrite()
{
}
