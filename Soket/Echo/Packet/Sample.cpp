#include "TPacket.h"

int SendMsg(SOCKET sock,const char* msg, WORD type)
{
	string address="서울 특별시";
	TPacket	sendPacket(type);
	sendPacket << msg;
	sendPacket << 1000;
	sendPacket << address;
	int iRet=send(sock, (char*)&sendPacket.m_uPacket,
		sendPacket.m_uPacket.ph.len +
		PACKET_HEADER_SIZE,0);

	char name[5] = { 0, };
	int iValue=0;
	string add;
	TPacket	recvPacket;
	recvPacket.m_uPacket.ph= sendPacket.m_uPacket.ph;
	memcpy(recvPacket.m_uPacket.msg,
			sendPacket.m_uPacket.msg,
			sizeof(char) * 256);
	recvPacket >> name;
	recvPacket >> iValue;
	recvPacket >> add;
	return iRet;
}

void main()
{
	SOCKET sock=0;
	SendMsg(sock, "game", PACKET_CHAT_MSG);
}