#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
using namespace std;

// 비동기 작업
// 로딩 화면에서 쓰면 될듯?!
OVERLAPPED OV; // 구조체
LARGE_INTEGER	g_size;
char* buf = NULL;


char * GetW2M(WCHAR* data) // 유니코드를 멀티바이트로 바꾸는 함수
{
	char cData[3333] = { 0, };

	int iLength = WideCharToMultiByte(
		CP_ACP, 0, data, -1, 0, 0, NULL, NULL);

	int iRet = WideCharToMultiByte(
		CP_ACP, 0, data, -1, cData, iLength, NULL, NULL);

	return cData;
}
WCHAR * GetM2W(char* data) // 멀티바이트를 유니코드로 바꾸는 함수
{
	WCHAR cData[3333] = { 0, };
	int iLength = MultiByteToWideChar(
		CP_ACP, 0, data, -1, 0, 0);

	int iRet = MultiByteToWideChar(
		CP_ACP, 0, data, -1, cData, iLength);

	return cData;
}
string w2m(wstring data) // 유니코드를 string으로 변경
{
	string ret = string(data.begin(), data.end());
	return ret;
}
wstring m2w(string data) // 유니코드를 string으로 변경
{
	wstring ret = wstring(data.begin(), data.end());
	return ret;
}


void FileRead(HANDLE hReadfile, DWORD offset)
{
	DWORD dwLength = 4096 * 1024; // filesize.QuadPart;
	g_size.QuadPart += offset;
	OV.Offset = g_size.LowPart;
	OV.OffsetHigh = g_size.HighPart;

	char* pTemp = &buf[g_size.QuadPart];

	DWORD dwRead;
	BOOL iRet = ReadFile(hReadfile, buf, dwLength,
		&dwRead, &OV);
	if (iRet == FALSE) // 이것이 아니라면 오류다 
	{
		if (GetLastError() == ERROR_IO_PENDING) // 읽고있으니 에러처리 하지마라
		{
			printf("\n%s", "Read ...."); // 이게 출력되느냐 안되느냐에 따라 비동기인지를 확인 할수 있다.
		}
	}
}
void main()
{

	//ZeroMemory(&OV, sizeof(OVERLAPPED));

	LARGE_INTEGER filesize; // LARGE_INTEGER : 24억 바이트
	DWORD dwLength = filesize.QuadPart;
	DWORD trans;

	HANDLE hReadfile = CreateFileA(
		"Bigfile.iso",
		GENERIC_READ, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_OVERLAPPED, NULL); // 파일을 연다
	if (hReadfile != INVALID_HANDLE_VALUE)
	{
		GetFileSizeEx(hReadfile, &filesize); // 파일사이즈의 크기 확인할수 있는 함수

		buf = new char[filesize.QuadPart];
		if (buf == NULL)
		{
			return;
		}
		FileRead(hReadfile, 0);
		OVERLAPPED OV; // 구조체
		ZeroMemory(&OV, sizeof(OVERLAPPED));



	}

	CloseHandle(hReadfile); // 파일을 닫는다.

	OVERLAPPED wOV;
	ZeroMemory(&wOV, sizeof(OVERLAPPED));
	HANDLE hWritefile = CreateFileA(
		"copy.txt",
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_OVERLAPPED, NULL); // 쓰기전용 txt 무조건 생성
	if (hWritefile != NULL)
	{
		DWORD trans = 0;
		DWORD dwWritten;
		bool iRet = WriteFile(hWritefile,
			buf, filesize.QuadPart,
			&dwWritten, &wOV);
		if (iRet == FALSE)
		{
			if (GetLastError() == ERROR_IO_PENDING) // 읽고있으니 에러처리 하지마라
			{
				printf("\n%s", "\nWrite ...."); // 이게 출력되느냐 안되느냐에 따라 비동기인지를 확인 할수 있다.
			}

		}
		while (1)
		{
			BOOL ret = GetOverlappedResult( // 결과만을 확인하는 함수이다.
				hReadfile, &wOV, &trans, TRUE);
			if (ret == TRUE)
			{
				if (filesize.QuadPart <= g_size.QuadPart)
				{
					break;
				}
				//FileRead(hReadfile, trans);
				printf("\n%s", "\nfinish ....");
				break;
			}
			else
			{
				printf("\n%s", "\nREAD......");
			}


		}
		printf("파일 출력 완료 !");

		delete[] buf;
		CloseHandle(hWritefile); // 파일을 닫는다

	}
}