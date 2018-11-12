#include "sample.h"
// 테스트
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
		MessageBox(0, _T("CreateWindow 초기화 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	ShowCursor(TRUE);
	gSample.Run();
	return 1;
}