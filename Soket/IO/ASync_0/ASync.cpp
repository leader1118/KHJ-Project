#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
using namespace std;

// �񵿱� �۾�
// �ε� ȭ�鿡�� ���� �ɵ�?!
OVERLAPPED OV; // ����ü
LARGE_INTEGER	g_size;
char* buf = NULL;


char * GetW2M(WCHAR* data) // �����ڵ带 ��Ƽ����Ʈ�� �ٲٴ� �Լ�
{
	char cData[3333] = { 0, };

	int iLength = WideCharToMultiByte(
		CP_ACP, 0, data, -1, 0, 0, NULL, NULL);

	int iRet = WideCharToMultiByte(
		CP_ACP, 0, data, -1, cData, iLength, NULL, NULL);

	return cData;
}
WCHAR * GetM2W(char* data) // ��Ƽ����Ʈ�� �����ڵ�� �ٲٴ� �Լ�
{
	WCHAR cData[3333] = { 0, };
	int iLength = MultiByteToWideChar(
		CP_ACP, 0, data, -1, 0, 0);

	int iRet = MultiByteToWideChar(
		CP_ACP, 0, data, -1, cData, iLength);

	return cData;
}
string w2m(wstring data) // �����ڵ带 string���� ����
{
	string ret = string(data.begin(), data.end());
	return ret;
}
wstring m2w(string data) // �����ڵ带 string���� ����
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
	if (iRet == FALSE) // �̰��� �ƴ϶�� ������ 
	{
		if (GetLastError() == ERROR_IO_PENDING) // �а������� ����ó�� ��������
		{
			printf("\n%s", "Read ...."); // �̰� ��µǴ��� �ȵǴ��Ŀ� ���� �񵿱������� Ȯ�� �Ҽ� �ִ�.
		}
	}
}
void main()
{

	//ZeroMemory(&OV, sizeof(OVERLAPPED));

	LARGE_INTEGER filesize; // LARGE_INTEGER : 24�� ����Ʈ
	DWORD dwLength = filesize.QuadPart;
	DWORD trans;

	HANDLE hReadfile = CreateFileA(
		"Bigfile.iso",
		GENERIC_READ, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_OVERLAPPED, NULL); // ������ ����
	if (hReadfile != INVALID_HANDLE_VALUE)
	{
		GetFileSizeEx(hReadfile, &filesize); // ���ϻ������� ũ�� Ȯ���Ҽ� �ִ� �Լ�

		buf = new char[filesize.QuadPart];
		if (buf == NULL)
		{
			return;
		}
		FileRead(hReadfile, 0);
		OVERLAPPED OV; // ����ü
		ZeroMemory(&OV, sizeof(OVERLAPPED));



	}

	CloseHandle(hReadfile); // ������ �ݴ´�.

	OVERLAPPED wOV;
	ZeroMemory(&wOV, sizeof(OVERLAPPED));
	HANDLE hWritefile = CreateFileA(
		"copy.txt",
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_OVERLAPPED, NULL); // �������� txt ������ ����
	if (hWritefile != NULL)
	{
		DWORD trans = 0;
		DWORD dwWritten;
		bool iRet = WriteFile(hWritefile,
			buf, filesize.QuadPart,
			&dwWritten, &wOV);
		if (iRet == FALSE)
		{
			if (GetLastError() == ERROR_IO_PENDING) // �а������� ����ó�� ��������
			{
				printf("\n%s", "\nWrite ...."); // �̰� ��µǴ��� �ȵǴ��Ŀ� ���� �񵿱������� Ȯ�� �Ҽ� �ִ�.
			}

		}
		while (1)
		{
			BOOL ret = GetOverlappedResult( // ������� Ȯ���ϴ� �Լ��̴�.
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
		printf("���� ��� �Ϸ� !");

		delete[] buf;
		CloseHandle(hWritefile); // ������ �ݴ´�

	}
}