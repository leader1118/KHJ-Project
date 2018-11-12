#pragma once
#pragma once
#include <Windows.h>

#pragma pack(push,1)

typedef struct
{
	WORD len;
	WORD type;
}PACKET_HEADER;
typedef struct
{
	PACKET_HEADER ph;
	char msg[256];

}UPACKET, *P_UPACKET;

typedef struct
{
	byte szName[13];
	int iIndex;
	int iData[20];
}CHARACTER_INFO;

#pragma pack(pop)

#define PACKET_HEADER_SIZE 4
// TYPE
#define PACKET_CHAT_MSG 1000
#define PACKET_CREATE_CHARACTER 2000

// SEND

//char buffer[] = "KGCA";

//UPACKET packet;
//ZeroMemory(&packet, sizeof(packet));
//packet.ph.len = strlen(buffer);
//packet.ph.type = PACKET_CHAT_MSG;
//memcpy(packet.msg,buffer,strlen(buffer));
//send(sock, (char*)&packet, packet.ph.len,0);



//UPACKET packet;
//ZeroMemory(&packet, sizeof(packet));
//CHARACTER_INFO cInfo;
// cInfo.szName = ;
// cInfo.iIndex = ;
// cInfo.iData = ;
//packet.ph.len = strlen(cInfo);
//packet.ph.type = PACKET_CHAT_MSG;
//memcpy(packet.msg,(char*)cInfo,strlen(cInfo));
//send(sock, (char*)&packet, packet.ph.len,0);



// RECV

// char buffer[256]={0,};
//int recvbyte = 0;
//while (1)
//{

//	recvbyte += recv(sock, buffer[recvbyte], 
//		sizeof(char) * PACKET_HEADER_SIZE-recvbyte, 0);
//	if (recvbyte == PACKET_HEADER_SIZE)
//	{
//		UPACKET packet;
//		ZeroMemory(&packet, sizeof(packet));
//		memcpy(packet.ph, buffer,sizeof(char)*PACKET_HEADER_SIZE);
//		int rByte == 0;
//		do
//		{
//			rByte += recv(sock, 
//				packet.msg[rByte], 
//				sizeof(char)*packet.ph.len-rByte, 0);
//
//		} while (packet.ph.len > rByte)
//			recvbyte = 0;
//		switch (packet.ph.type)
//		{
//		case PACKET_CHAT_MSG:
//			{
//				printf("패킷 완성%s",packet.msg);
//			}break;
//		case PACKET_CREATE_CHARACTER:
//			{
//				CHARACTER_INFO cInfo;
//				memcpy(cInfo, packet.msg, sizeof(CHARACTER_INFO));
//			}break;
//			
//			
//		}
//			
//	}
//}