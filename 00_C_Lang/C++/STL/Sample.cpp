#include <string>
#include <iostream>
#include <tchar.h>
void printer(char* pData)
{
	std::cout << pData;
}
void main()
{
	TCHAR data[] = _T("kgca");
	TCHAR dataA[] = _T("game");
	//UNICODE<->MULTIBYTE
	//std::wstring copyA = data;
	std::string copyData;
	

	if (copyA == copyData)
	{

	}
	copyData = data;
	copyData += dataA;
	std::cout << copyData;
		printer(copyData.c_str());

	/*char copyData[256] = { 0, };
	strcpy(copyData, data);
	strcat(copyData, "game");
	memcpy(copyData, data, sizeof(char)*strlen(data));
	if (strcmp(data, copyData) == 0)*/
}