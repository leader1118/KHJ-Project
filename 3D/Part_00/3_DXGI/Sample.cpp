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
		MessageBox(NULL, _T("������ �������� ���߽��ϴ�."), _T("���� ���� ����"), MB_ICONERROR);
		return FALSE;
	}
	DEnumAdapter* pAdapterInfo;
	_ftprintf(fp, L"Num Adapter: %d\n", m_Enumeration)
}