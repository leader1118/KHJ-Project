#include "S_SvrUser.h"

void S_SvrUser::Dispatch(DWORD dwByteSize, LPOVERLAPPED Ov)
{
	OVERLAPPEDEX* pOv = (OVERLAPPEDEX*)Ov;
	if (dwByteSize == 0)
	{
		return;
	}
	if (pOv->i_Flags == OVERLAPPEDEX::MODE_RECV)
	{
		m_StreamPacket.Put(m_szRecvBuf.buf, dwByteSize, this);
	}
	if (pOv->i_Flags == OVERLAPPEDEX::MODE_SEND)
	{

	}
	WaitforPacketReceive();
	
}

void S_SvrUser::AddPacket(PACKET& addPacket)
{
	{
		S_Lock Lock(this);
		m_StreamPacket.PacketList.push_back(addPacket);
	}
	return;
}

bool S_SvrUser::Create()
{
	ZeroMemory(&m_OV, sizeof(m_OV));
	WaitforPacketReceive();
	return true;
}

void S_SvrUser::WaitforPacketReceive()
{
	DWORD Transferred, flag = 0;
	m_szRecvBuf.buf = m_strBuffer;
	m_szRecvBuf.len = 4096;
	int ret = WSARecv(m_Socket, &m_szRecvBuf, 1, &Transferred, &flag,
		(LPOVERLAPPED)&m_OV, NULL);

	if (ret == SOCKET_ERROR)
	{
		int Error = WSAGetLastError();
		if (Error != WSA_IO_PENDING)
		{
			int i = 0;
		}
	}
}

bool S_SvrUser::Run()
{
	char szMsgBuf[2048] = { 0, };
	int strlen = 0;
	while (1)
	{
		strlen = recv(m_Socket, szMsgBuf, sizeof(szMsgBuf), 0);
		if (strlen <= 0)break;
		szMsgBuf[strlen] = 0;
		m_StreamPacket.Put(szMsgBuf, strlen, this);
		Sleep(10);
	}
	DeleteUser(m_Socket);
	return true;
}
void S_SvrUser::DeleteUser(SOCKET socket)
{

}
void S_SvrUser::DeleteUser()
{

}
S_SvrUser::S_SvrUser()
{
	m_Socket = 0;
}


S_SvrUser::~S_SvrUser()
{
	closesocket(m_Socket);
}
