#include "SProtocol.h"

#define PACKET_CHAR_NAME_REQ 1000
#define PACKET_CHAR_NAME_ACK 1001
#define PACKET_CHAR_MSG 1002

#pragma pack(push,1)

typedef struct
{
	WORD user_idx; // 캐릭터의 고유한 인덱스
	WORD PosX;
	WORD PosY;
	WORD direction;
}SPACKET_USER_POSITION;
#define PACKET_USER_POSITION 3000

#pragma pack(pop)