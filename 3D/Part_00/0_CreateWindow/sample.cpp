#include "sample.h"
// �׽�Ʈ
Sample::Sample(void)
{

}
Sample::~Sample(void)
{

}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdshow)
{
	Sample gSample;
	if (!gSample.InitWindow(hInstance, nCmdshow, L"CreateWindow"))
	{
		MessageBox(0, _T("CreateWindow �ʱ�ȭ ����"), _T("Fatal error"), MB_OK);
		return 0;
	}
	ShowCursor(TRUE);
	gSample.Run();
	return 1;
}