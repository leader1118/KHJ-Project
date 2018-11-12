#pragma once
#include <iostream>
#include <string>
#include <WinSock2.h> // ������ ���� �־�� �Ѵ�.
#pragma comment(lib,"ws2_32")
#include "TProtocol.h"
using namespace std;
class TPacket
{
public:
	//PACKET_HEADER ph; ����ü�� ����ص� ����� ����.
	//char*		m_pData;
	//WORD		m_iSize;
	//WORD		m_iType;
	UPACKET		m_uPacket;
	char*		m_pOffset;
public:
	void		PutData(const char* pData,int iSize);
	TPacket&	operator << (const char* data);
	TPacket&	operator << (int data);
	//TPacket&	operator << (float data);
	//TPacket&	operator << (DWORD data);
	TPacket&	operator << (string data);
public:
	void		GetData(const char* pData, int iSize);
	TPacket&	operator >> (const char* data);
	TPacket&	operator >> (int& data);
	TPacket&	operator >> (string& data);
public:
	TPacket();
	TPacket(WORD type);
	virtual ~TPacket();
};

