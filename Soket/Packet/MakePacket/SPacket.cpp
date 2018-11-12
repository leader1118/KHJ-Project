#include "SPacket.h"

void SPacket::PutData(const char* pData,
	int iSize)
{
	m_uPacket.ph.len += iSize;
	memcpy(m_pOffset, pData, iSize);
	m_pOffset += iSize;
}
void SPacket::GetData(const char* pData,
	int iSize)
{
	memcpy(const_cast<char*>(pData),
		m_pOffset, iSize);
	m_pOffset += iSize;
}
SPacket & SPacket::operator << (int data)
{
	PutData((char*)&data, sizeof(int));
	return *this;
}
SPacket & SPacket::operator << (short data)
{
	PutData((char*)&data, sizeof(short));
	return *this;
}
SPacket & SPacket::operator << (long data)
{
	PutData((char*)&data, sizeof(long));
	return *this;
}
SPacket & SPacket::operator << (DWORD data)
{
	PutData((char*)&data, sizeof(DWORD));
	return *this;
}
SPacket & SPacket::operator << (float data)
{
	PutData((char*)&data, sizeof(float));
	return *this;
}
SPacket & SPacket::operator << (char* data)
{
	int iSize = strlen(data) + 1;
	PutData(data, iSize);
	return *this;
}
SPacket & SPacket::operator << (string data)
{
	PutData(data.c_str(), data.size());
	return *this;
}
/////////////////////////////////
SPacket & SPacket::operator >> (int& data)
{
	GetData((char*)&data, sizeof(int));
	return *this;
}
SPacket & SPacket::operator >> (short& data)
{
	GetData((char*)&data, sizeof(short));
	return *this;
}
SPacket & SPacket::operator >> (long& data)
{
	GetData((char*)&data, sizeof(long));
	return *this;
}
SPacket & SPacket::operator >> (DWORD& data)
{
	GetData((char*)&data, sizeof(DWORD));
	return *this;
}
SPacket & SPacket::operator >> (float& data)
{
	GetData((char*)&data, sizeof(float));
	return *this;
}
SPacket & SPacket::operator >> (char* data)
{
	int iSize = strlen(m_pOffset) + 1;
	GetData(data, iSize);
	return *this;
}
SPacket & SPacket::operator >> (string& data)
{
	int ilen = strlen(m_pOffset) + 1;
	char buffer[256] = { 0, };
	GetData(buffer, ilen);
	data = buffer;
	return *this;
}
SPacket::SPacket()
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_pOffset = m_uPacket.msg;
}
SPacket::SPacket(int  dwType)
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_uPacket.ph.len = 0;
	m_uPacket.ph.type = dwType;
	m_pOffset = m_uPacket.msg;
}



SPacket::~SPacket()
{
}
