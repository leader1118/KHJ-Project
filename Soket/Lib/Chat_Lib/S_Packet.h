#pragma once
#include "S_Protocol.h"

class S_Packet
{
public:
	PTR_HEADER_PACKET	m_ptrPacket;
	char		m_strPacketbuf[PACKETBUFFERSIZE];
	char*		m_pStrWritePos;
	char*		m_pStrReadPos;
	int			m_iReceivedsize;
public:
	WORD		getID();
	WORD		getSize();
	char*		getData();
	int			getDataSize();
public:
	void		ReadData(void* buf, int iSize);
	void		WriteData(void* buf, int iSize);
	void		Clear();
public:
	S_Packet& SetId(unsigned short id);
public:
	S_Packet&		operator << (int arg);	
	S_Packet&		operator << (DWORD arg);	
	S_Packet&		operator << (bool arg);	
	S_Packet&		operator << (unsigned short arg);	
	S_Packet&		operator << (float arg);	
	S_Packet&		operator << (char* arg);	
	S_Packet&		operator << (S_Packet& arg);
	
public:
	S_Packet&		operator >> (int& arg);
	S_Packet&		operator >> (DWORD& arg);
	S_Packet&		operator >> (bool& arg);
	S_Packet&		operator >> (unsigned short& arg);
	S_Packet&		operator >> (float& arg);
	S_Packet&		operator >>	(char* arg);
	S_Packet&		operator >> (S_Packet& arg);

public:
	S_Packet();
	S_Packet(unsigned short type);
	virtual ~S_Packet();
};

