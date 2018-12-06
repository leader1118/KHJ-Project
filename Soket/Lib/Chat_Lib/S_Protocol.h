#pragma once
#ifndef SPROTOCAL_HEADER
#define SPROTOCAL_HEADER
#include "S_Std.h"
#define PACKET_HEADER_SIZE 4
#pragma pack(push,1)
typedef struct
{
	WORD len;
	WORD type;
}PACKET_HEADER;
typedef struct
{
	PACKET_HEADER ph;
	char		  msg[2048];
}UPACKET, *P_UPACKET;

typedef struct
{
	int User_iIndex;
	BYTE	POS_X;
	BYTE	POS_Y;
	BYTE	bDirection;
}SPACKET_USER_POSITON;
#define PACKET_USER_POSITON		3000

class S_SvrUser;
typedef struct 
{
	UPACKET packet;
	S_SvrUser* pUser;
}PACKET, *PTR_PACKET;

typedef struct
{
	int		UserIndex;
	char	User_ID[21];
	char	User_PS[15];
}SPACKET_USER_LOGIN;
#define PACKET_USER_LOGIN		2000

#define PACEKT_CHAT_NAME_REQ		1000 // 대화명 입력

#define PACKET_CHAT_NAME_ACK		1001 // 대화명 입력 전송

#define PACKET_CHAT_MSG				1002 // 대화명 입력 전송

typedef struct
{
	WORD user_idx;
	WORD PosX;
	WORD PosY;
	WORD direction;
}SPACKET_USER_POSITION;
#define PACKET_USER_POSITION 3000
#pragma pack(pop)
#endif