#include "S_Packet.h"

WORD S_Packet::getID()
{
	return *m_ptrPacket.type;
}
WORD S_Packet::getSize()
{
	return *m_ptrPacket.len;
}
char* S_Packet::getData()
{
	return m_strPacketbuf;
}
int S_Packet::getDataSize()
{
	return m_iReceivedsize;
}
void S_Packet::ReadData(void* buf, int iSize)
{
	::CopyMemory(buf, m_pStrReadPos, iSize);
	m_pStrReadPos += iSize;
}

void S_Packet::WriteData(void* buf, int iSize)
{
	if (m_iReceivedsize >= PACKETBUFFERSIZE - 4)
	{

	}
	*m_ptrPacket.len += iSize;
	CopyMemory(m_pStrWritePos, buf, iSize);
	m_pStrWritePos += iSize;
	m_iReceivedsize += iSize;
}
S_Packet& S_Packet::SetId(unsigned short id)
{
	*m_ptrPacket.type = id;
	return *this;
}
void S_Packet::Clear()
{
	ZeroMemory(m_strPacketbuf, PACKETBUFFERSIZE);
	m_ptrPacket.len = (WORD*)m_strPacketbuf + 0;
	m_ptrPacket.type = (WORD*)m_strPacketbuf + 2;
	m_pStrWritePos = &m_strPacketbuf[4];
	m_pStrReadPos = &m_strPacketbuf[4];
	m_iReceivedsize = 0;
	*m_ptrPacket.len = 4;
}

S_Packet& S_Packet::operator << (int arg)
{
	WriteData(&arg, sizeof(int));
	return *this;
}

S_Packet& S_Packet::operator >> (int& arg)
{
	ReadData(&arg, sizeof(int));
	return *this;
}

S_Packet& S_Packet::operator << (DWORD arg)
{
	WriteData(&arg, sizeof(DWORD));
	return *this;
}

S_Packet& S_Packet::operator >> (DWORD& arg)
{
	ReadData(&arg, sizeof(DWORD));
	return *this;
}

S_Packet& S_Packet::operator << (bool arg)
{
	WriteData(&arg, sizeof(bool));
	return *this;
}

S_Packet& S_Packet::operator >> (bool& arg)
{
	ReadData(&arg, sizeof(bool));
	return *this;
}

S_Packet& S_Packet::operator << (unsigned short arg)
{
	WriteData(&arg, sizeof(unsigned short));
	return *this;
}

S_Packet& S_Packet::operator >> (unsigned short& arg)
{
	ReadData(&arg, sizeof(unsigned short));
	return *this;
}

S_Packet& S_Packet::operator << (float arg)
{
	WriteData(&arg, sizeof(float));
	return *this;
}

S_Packet& S_Packet::operator >> (float& arg)
{
	ReadData(&arg, sizeof(float));
	return *this;
}

S_Packet& S_Packet::operator << (char* arg)
{
	int iLen = sizeof(char)*strlen(arg);
	WriteData(&arg, iLen);
	return *this;
}

S_Packet& S_Packet::operator >> (char* arg)
{
	int iLen = sizeof(char)*strlen(this->m_pStrReadPos);
	ReadData(&arg, sizeof(char)*iLen);
	return *this;
}

S_Packet& S_Packet::operator << (S_Packet& arg)
{
	unsigned short type = arg.getID();
	unsigned short size = arg.getSize();

	WriteData(&type, sizeof(unsigned short));
	WriteData(&size, sizeof(unsigned short));
	WriteData(&arg.m_pStrWritePos, size - 4);
	return *this;
}

S_Packet& S_Packet::operator >> (S_Packet& arg)
{
	int type, size;
	char buffer[4096] = { 0, };
	ReadData(&type, sizeof(unsigned short));
	ReadData(&size, sizeof(unsigned short));
	ReadData(&buffer, size - 4);

	arg.SetId(type);
	arg.WriteData(buffer, size - 4);
	return *this;
}

S_Packet::S_Packet()
{
	Clear();
	SetId(0);
}
S_Packet::S_Packet(unsigned short type)
{
	Clear();
	SetId(type);
}


S_Packet::~S_Packet()
{
}
