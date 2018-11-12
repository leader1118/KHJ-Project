#include "TPacket.h"

void TPacket::PutData(const char* pData,int iSize)
{
	m_uPacket.ph.len += iSize;
	memcpy(m_pOffset, pData, iSize);
	m_pOffset += iSize;
}
TPacket& TPacket::operator<< (const char* data)
{
	int iSize = strlen(data)+1;
	PutData(data, iSize);
	return *this;
}
TPacket& TPacket::operator<< (int data)
{
	
	PutData((char*)&data, sizeof(int));
	return *this;
}
TPacket& TPacket::operator<< (string data)
{
	PutData(data.c_str(), data.size());
	return *this;
}



void TPacket::GetData(const char* pData, int iSize)
{
	memcpy(const_cast<char*>(pData),m_pOffset,iSize);
	m_pOffset += iSize;
}
TPacket& TPacket::operator>> (string& data)
{
	int iSize = strlen(m_pOffset) + 1;
	char buffer[256] = { 0, };
	GetData(buffer, iSize);
	data = buffer;
	return *this;
}
TPacket& TPacket::operator>> (const char* data)
{
	int iSize = strlen(m_pOffset) + 1;
	GetData(data, iSize);
	return *this;
}
TPacket& TPacket::operator>> (int& data)
{
	GetData((char*)&data, sizeof(int));
	return *this;
}


TPacket::TPacket(WORD type)
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_uPacket.ph.type = type;
	m_pOffset = m_uPacket.msg;
}


TPacket::TPacket()
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_pOffset = m_uPacket.msg;
}


TPacket::~TPacket()
{
}
