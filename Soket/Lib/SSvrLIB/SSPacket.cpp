#include "SSPacket.h"

// SSPacket packet;
// int id , ps , money;
// char email[30], address[30];
// packet.SetID(1002) << id << ps;
// packet.SetID(1002) << id << ps << email << addree << money;
// packet.SetID(1002) >> id >> ps >> email >> addree >> money;

// SSPacket packet(1002);
// packet << id << ps;
// packet >> id >> ps;

WORD SSPacket::GetID()
{
	return *m_PacketHeader.type;
}
WORD SSPacket::GetSize()
{
	return *m_PacketHeader.len;
}
char* SSPacket::GetData()
{
	return m_strPacketBuffer;
}
int SSPacket::GetDataSize()
{
	return m_iReceivedSize;
}

void SSPacket::ReadData(void* buffer, int iSize)
{
	::CopyMemory(buffer, m_pstrReadPosition, iSize);
	m_pstrReadPosition += iSize;
};

void SSPacket::WriteData(void* buffer, int iSize)
{
	if (m_iReceivedSize >= PACKETBUFFERSIZE - 4)
	{
		// 오류
	}
	*m_PacketHeader.len += iSize;
	CopyMemory(m_pstrWritePosition, buffer, iSize);
	// 1차원 배열의 주소가 이동
	m_pstrWritePosition += iSize;
	// 실제 데이터의 바이트 용량
	m_iReceivedSize += iSize;
};

SSPacket& SSPacket::SetID(unsigned short ID)
{
	*m_PacketHeader.type = ID;
	return *this;
};
// 패킷을 생성할 떄 sum - a.v + b.v + c.v + d.v + e.v;
SSPacket& SSPacket::operator << (int arg)
{
	WriteData(&arg, sizeof(int));
	return *this;
};
SSPacket& SSPacket::operator >> (int& arg)
{
	WriteData(&arg, sizeof(int));
	return *this;
};

SSPacket& SSPacket::operator << (DWORD arg)
{
	WriteData(&arg, sizeof(DWORD));
	return *this;
};

SSPacket& SSPacket::operator >> (DWORD& arg)
{
	ReadData(&arg, sizeof(DWORD));
	return *this;
};

SSPacket& SSPacket::operator << (bool arg)
{
	WriteData(&arg, sizeof(bool));
	return *this;
};
SSPacket& SSPacket::operator >> (bool& arg)
{
	ReadData(&arg, sizeof(bool));
	return *this;
};

SSPacket& SSPacket::operator << (unsigned short arg)
{
	WriteData(&arg, sizeof(unsigned short));
	return *this;
};
SSPacket& SSPacket::operator >> (unsigned short& arg)
{
	ReadData(&arg, sizeof(unsigned short));
	return *this;
}

SSPacket& SSPacket::operator << (float arg)
{
	WriteData(&arg, sizeof(float));
	return *this;
};
SSPacket& SSPacket::operator >> (float& arg)
{
	ReadData(&arg, sizeof(float));
	return *this;
};

SSPacket& SSPacket::operator << (char* arg)
{
	int iLen = sizeof(char)*strlen(arg);
	WriteData(&arg, iLen);
	return *this;
};

SSPacket& SSPacket::operator >> (char* arg)
{
	int iLen = sizeof(char)*strlen(this->m_pstrReadPosition);
	ReadData(&arg, sizeof(char)*iLen);
	return *this;
};

SSPacket& SSPacket::operator << (SSPacket& arg)
{
	unsigned short type = arg.GetID();
	unsigned short size = arg.GetSize();

	WriteData(&type, sizeof(unsigned short));
	WriteData(&size, sizeof(unsigned short));
	WriteData(&arg.m_pstrWritePosition, size - 4);
	return *this;
};

SSPacket& SSPacket::operator >> (SSPacket& arg)
{
	int type, size;
	char buffer[4069] = { 0, };
	ReadData(&type, sizeof(unsigned short));
	ReadData(&size, sizeof(unsigned short));
	ReadData(&buffer, size - 4);

	arg.SetID(type);
	arg.WriteData(buffer, size - 4);
	return *this;
};
void SSPacket::Clear()
{
	ZeroMemory(m_strPacketBuffer, PACKETBUFFERSIZE);
	m_PacketHeader.len = (WORD*)m_strPacketBuffer + 0;
	m_PacketHeader.type = (WORD*)m_strPacketBuffer + 2;
	m_pstrWritePosition = &m_strPacketBuffer[4];
	m_pstrReadPosition = &m_strPacketBuffer[4];
	m_iReceivedSize = 0;
	*m_PacketHeader.len = 4;
}


SSPacket::SSPacket(void)
{
	Clear();
	SetID(0);
}
SSPacket::SSPacket(unsigned short type)
{
	Clear();
	SetID(type);
}

SSPacket::~SSPacket(void)
{
}
