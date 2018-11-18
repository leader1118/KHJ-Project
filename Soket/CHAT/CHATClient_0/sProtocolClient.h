#ifndef MUTEX_SAMPLE
#define MUTEX_SAMPLE
#include "SProtocol.h"

#pragma pack(push,1)
typedef struct
{
	int User_iIndex;
	BYTE	POS_X;
	BYTE	POS_Y;
	BYTE	bDirection;
}SPACKET_USER_POSITON;
#define PACKET_USER_POSITON		3000

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

#pragma pack(pop)

#endif