//#include <Windows.h>
//#include <iostream>
//#include <tchar.h>
//#include <string>
//using namespace std;
//
//
//char * GetW2M(WCHAR* data) // �����ڵ带 ��Ƽ����Ʈ�� �ٲٴ� �Լ�
//{
//	char cData[3333] = { 0, };
//
//	int iLength = WideCharToMultiByte(
//		CP_ACP, 0, data, -1, 0, 0, NULL, NULL);
//
//	int iRet = WideCharToMultiByte(
//		CP_ACP, 0, data, -1, cData, iLength, NULL, NULL);
//
//	return cData;
//}
//WCHAR * GetM2W(char* data) // ��Ƽ����Ʈ�� �����ڵ�� �ٲٴ� �Լ�
//{
//	WCHAR cData[3333] = { 0, };
//	int iLength = MultiByteToWideChar(
//		CP_ACP, 0, data, -1, 0, 0);
//
//	int iRet = MultiByteToWideChar(
//		CP_ACP, 0, data, -1, cData, iLength);
//
//	return cData;
//}
//string w2m(wstring data) // �����ڵ带 string���� ����
//{
//	string ret = string(data.begin(),data.end());
//	return ret;
//}
//wstring m2w(string data) // �����ڵ带 string���� ����
//{
//	wstring ret = wstring(data.begin(), data.end());
//	return ret;
//}
//
//
//
//void main()
//{
//	HANDLE hWritefile = CreateFile(
//		L"test.txt",
//		GENERIC_WRITE, 0, NULL,
//		CREATE_ALWAYS,
//		FILE_ATTRIBUTE_NORMAL, NULL); // �������� txt ������ ����
//	if (hWritefile != NULL)
//	{
//		TCHAR buf[] = L"asasasasasas";
//		DWORD dwLength = sizeof(buf);
//		DWORD dwWritten;
//		bool iRet=WriteFile(hWritefile,buf,dwLength,
//			&dwWritten,NULL);
//		if (iRet == TRUE)
//		{
//			printf("��¿Ϸ�");
//		}
//	}
//	CloseHandle(hWritefile); // ������ �ݴ´�
//	
//	
//	
//	HANDLE hReadfile = CreateFile(
//		L"test.txt",
//		GENERIC_READ, 0, NULL,
//		OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL, NULL); // ������ ����
//	if (hReadfile != NULL)
//	{
//		TCHAR buf[1024] = { 0, };
//		DWORD dwLength = sizeof(buf);
//		DWORD dwRead;
//		bool iRet = ReadFile(hReadfile, buf, dwLength,
//			&dwRead, NULL);
//		if (iRet == TRUE)
//		{
//			wstring strWData = buf;
//			string strCData= w2m(strWData);
//
//			printf("\n%s", strCData.c_str());
//			_tcprintf(L"\n%s", m2w(strCData.c_str()));
//
//			printf("\n%s", strCData.c_str());
//
//			char* pData = GetW2M(buf);
//			printf("\n%s", pData);
//
//			char dddd[] = "aaaaa";
//			wprintf(L"\n%s", GetM2W(pData));
//
//			//_tcprintf(L"\n%s", buf);
//		}
//	}
//	CloseHandle(hReadfile); // ������ �ݴ´�.
//}