#include "Sample.h"

bool	Sample::Init()
{
	DXDevice::CreateGIFactory();
	// =--------------------------------------------=
	//
	// =--------------------------------------------=
	FILE *fp;
	fp  = _tfopen(_T("DeviceInfo.txt"), _T("wt"));
	if (!fp)
	{
		MessageBox(NULL, _T("파일을 생성하지 못했습니다."), _T("파일 생성 에러"), MB_ICONERROR);
		return FALSE;
	}
	DEnumAdapter* pAdapterInfo;
	_ftprintf(fp, L"Num Adapter: %d\n", m_Enumeration)
}