#include "S_StreamPacket.h"
#include "S_Server.h"

void S_StreamPacket::Put(char* recvBuffer, int Size, S_SvrUser* pUser)
{
	if (m_iWritePos + Size >= MAX_RECV)
	{
		char cTemp[MAX_RECV] = { 0, };
		memcpy(cTemp, &RecvBuffer[m_iStartPos], m_iReadPos);
		ZeroMemory(&RecvBuffer, sizeof(char)*MAX_RECV);
		memcpy(&RecvBuffer, &cTemp, m_iReadPos);
		m_pPacket = (P_UPACKET)RecvBuffer;
		m_iStartPos = 0;
		m_iWritePos = m_iReadPos;
	}

	memcpy(&RecvBuffer[m_iWritePos], recvBuffer, Size);
	m_iWritePos += Size;
	m_iReadPos += Size;

	if (m_iReadPos < PACKET_HEADER_SIZE)
	{
		return;
	}

	m_pPacket = (P_UPACKET)&RecvBuffer[m_iStartPos];
	if (m_iReadPos >= m_pPacket->ph.len)
	{
		do {
			PACKET Add;
			ZeroMemory(&Add, sizeof(Add));
			memcpy(&Add.packet, &RecvBuffer[m_iStartPos], m_pPacket->ph.len);
			Add.pUser = pUser;

			if (pUser != NULL)
			{
				pUser->AddPacket(Add);
			}
			m_iReadPos -= m_pPacket->ph.len;
			m_iStartPos += m_pPacket->ph.len;

			if (m_iReadPos < MAX_RECV)
			{
				break;
			}
			m_pPacket = (P_UPACKET)&RecvBuffer[m_iStartPos];
		} while (m_iReadPos >= m_pPacket->ph.len);
	}
}

S_StreamPacket::S_StreamPacket()
{
	ZeroMemory(RecvBuffer, sizeof(char)*MAX_RECV);
	m_iStartPos = 0;
	m_iWritePos = 0;
	m_iReadPos = 0;
	m_pPacket = NULL;
}


S_StreamPacket::~S_StreamPacket()
{
}
