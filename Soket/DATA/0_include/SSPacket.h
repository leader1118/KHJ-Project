#pragma once
#include "SvrStd.h"

#define PACKETBUFFERSIZE 8192
class SSPacket
{
public:
	typedef struct
	{
		WORD* len;
		WORD* type;
	}PACKETHEADER;
public:
	PACKETHEADER	m_PacketHeader;
	char			m_strPacketBuffer[PACKETBUFFERSIZE];
	char*			m_pstrWritePosition;
	char*			m_pstrReadPosition;

	WORD			GetID();
	WORD			GetSize();
	int				m_iReceivedSize;
	int				GetDataSize();
	void			ReadData(void* buffer, int iSize);
	void			WriteData(void* buffer, int iSize);

public:
	SSPacket&	SetID(unsigned short ID);
	// 패킷을 생성할 떄
	SSPacket&	operator << (int arg);
	// 패킷에서 데이터를 추출할 떄
	SSPacket&	operator >> (int& arg);

	SSPacket&	operator << (DWORD arg);
	SSPacket&	operator >> (DWORD& arg);

	SSPacket&	operator << (bool arg);
	SSPacket&   operator >> (bool& arg);

	SSPacket&   operator << (unsigned short arg);
	SSPacket&	operator >> (unsigned short& arg);

	SSPacket&	operator << (float arg);
	SSPacket&   operator >> (float& arg);

	SSPacket&	operator << (char* arg);
	SSPacket&	operator >> (char* arg);
	SSPacket&	operator << (SSPacket& arg);
	SSPacket&	operator >> (SSPacket& arg);

	char*		GetData();
	void		Clear();
public:
	SSPacket(void);
		SSPacket(unsigned short type);
	virtual ~SSPacket(void);
};

