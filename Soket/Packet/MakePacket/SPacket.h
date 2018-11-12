#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include "SProtocol.h"
#pragma comment (lib,"ws2_32.lib")

using namespace std;

typedef basic_string<TCHAR> T_STR;
typedef basic_string<wchar_t> W_STG;
typedef basic_string<char> C_STR;

//	struct TUserData{header, name[9],age };
//	사용방법 (1)
//	준비 : char buffer[2048] = {0,};
//	SPaket data;
//	data << header;
//	data << " 김현진 ";
//	data << age;

//	사용방법(2)
//	data << header << "김현진" << 25;
//	char buffer[2048] ={0,};
//	SPaket data;
//	data >> header;
//	data >> " 김현진 " ;
//  data >> age;

//	사용방법 (2)
//	data >> header >> "김현진" >> 25;

class SPacket
{
public:
	char* m_pOffset;
	UPACKET m_uPacket;
public:
	void	PutData(const char* pData, int iSize);
	void	GetData(const char* pData, int iSize);
public:
	// 연산자 재정의 
	SPacket & operator << (int data);
	SPacket & operator << (short data);
	SPacket & operator << (long data);
	SPacket & operator << (float data);
	// SPacket & operator << (byte data);
	SPacket & operator << (char* data);
	SPacket & operator << (DWORD data);
	SPacket & operator << (string data);

	SPacket & operator >> (int& data);
	SPacket & operator >> (short& data);
	SPacket & operator >> (long& data);
	SPacket & operator >> (float& data);
	//SPacket & operator >> (byte& data);
	SPacket & operator >> (char* data);
	SPacket & operator >> (DWORD& data);
	SPacket & operator >> (string& data);

public:
	SPacket();
	SPacket(int dwType);
	virtual ~SPacket();
};

