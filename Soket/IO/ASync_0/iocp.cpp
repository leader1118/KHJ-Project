#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <conio.h>
using namespace std;
#define MAX_WORK_THREAD 4
#define MAX_READ_SZIE 4096

// �߿�
class TIocp
{
public:
	HANDLE	m_hIOCP;
	HANDLE	m_hFileRead;
	HANDLE	m_hFileWrite;
	OVERLAPPED m_hReadOV;
	OVERLAPPED m_hWriteOV;
	HANDLE	m_hEventKillThread;
	HANDLE	m_hWorkThread[MAX_WORK_THREAD];
	char	m_szReadBuffer[MAX_READ_SZIE];
public:
	void Init();
	void Frame();
	bool WaitForRead();
	bool DispatchRead(DWORD dwTransfer);
	bool DispatchWrite(DWORD dwTransfer);

	static DWORD WINAPI WorkerThread(LPVOID parameter);
public:
	~TIocp() {}
	void Release()
	{
		CloseHandle(m_hFileRead);
		CloseHandle(m_hFileWrite);
		CloseHandle(m_hIOCP);
		CloseHandle(m_hWorkThread[0]);
		CloseHandle(m_hWorkThread[1]);
		CloseHandle(m_hWorkThread[2]);
		CloseHandle(m_hWorkThread[3]);
	}
};
DWORD WINAPI TIocp::WorkerThread(LPVOID parameter)
{
	TIocp* iocp = (TIocp*)parameter;
	OVERLAPPED ov;
	DWORD  bytesTransfer;
	ULONG_PTR keyValue;
	
	while (1)
	{

		if (WAIT_OBJECT_0	==	::WaitForSingleObject(iocp->m_hEventKillThread, 1));
		{
			break;
		}
		// IOCP QUEUE // GetQueuedCompletionStatus = QUEUE�� �ִ� �����͸� ���´�.
		BOOL bRet=::GetQueuedCompletionStatus(iocp->m_hIOCP,  
			&bytesTransfer,&keyValue,
			(LPOVERLAPPED*)&ov,1);
		if (bRet == TRUE) // Read �۾��� �Ϸ�Ǹ� ������Ʈ�� ���⿡ ������.
		{
			if (keyValue == (ULONG_PTR)iocp->m_hFileRead)
			{
				iocp->DispatchRead(bytesTransfer);
			}
			else
			{
				iocp->DispatchWrite(bytesTransfer);
			}
		}
		else
		{
			if (GetLastError() == WAIT_TIMEOUT)
			{
				continue;
			}
			//.......
		}
	}
	return 0;
}
bool TIocp::DispatchRead(DWORD dwTransfer)
{
	DWORD dwWrite;
	if(::WriteFile(m_hFileWrite,m_szReadBuffer,dwTransfer,&dwWrite,(LPOVERLAPPED)&m_hWriteOV)==FALSE);
	{
		if (GetLastError() != ERROR_IO_PENDING) // �ٽ����� �۾�
		{
			return false;
		}
	}
	
	LARGE_INTEGER data;
	data.QuadPart = dwTransfer;
	m_hReadOV.Offset += data.LowPart;
	m_hReadOV.OffsetHigh += data.HighPart;

	WaitForRead();
	return true;
}
bool TIocp::DispatchWrite(DWORD dwTransfer)
{
	LARGE_INTEGER data;
	data.QuadPart = dwTransfer;
	m_hWriteOV.Offset += data.LowPart;
	m_hWriteOV.OffsetHigh += data.HighPart;

	return true;
}



void TIocp::Init()
{
	m_hFileRead = CreateFile( // �а�
		L"aaaa.zip",
		GENERIC_READ, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_OVERLAPPED, 0);

	m_hFileWrite = CreateFile( // ����
		L"copy.zip", 
		GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_OVERLAPPED, 0);
	DWORD id;
	for (int i = 0; i < MAX_WORK_THREAD; i++)
	{
		m_hWorkThread[i] = ::CreateThread(0, 0, WorkerThread, this, 0, &id);
	}

	m_hEventKillThread = ::CreateEvent(0, TRUE, FALSE,L"EventKillThread");
	::ResetEvent(m_hEventKillThread);

	m_hIOCP=::CreateIoCompletionPort(INVALID_HANDLE_VALUE,0,0,0); 
	// iocp m_gIOCP= �����,�߰����� ��Ȱ // m_hIOCP �ڵ��� ������ �Ѵ�. �ٸ� �������� �۾��� Ȯ���Ҽ� �ִ�.


	::CreateIoCompletionPort(m_hFileRead,m_hIOCP,(ULONG_PTR)m_hFileRead,0);			//key == �Ϸ�Ű // ULONG_PTR ��ſ� DWORD�� �־ �ȴ�.
	::CreateIoCompletionPort(m_hFileWrite,m_hIOCP, (ULONG_PTR)m_hFileWrite,0);

}
bool TIocp::WaitForRead()
{
	DWORD dwReadBytes = 0;
	if (::ReadFile(m_hFileRead,m_szReadBuffer, MAX_READ_SZIE, &dwReadBytes,&m_hReadOV)==FALSE)   // :: ���� �ذ� ������. // �񵿱� �۾�
	{
		if (GetLastError() == ERROR_IO_PENDING) // �ٽ����� �۾�
		{
			return true;
		}
		return false;
	}
	//else // true �����Ŵ�.. �� ������ // Ȥ�� �� ERROR ������ Ȯ���Ѵ�. // ��ǻ� ��� �ȴ�. ���������� ���ư��ٸ� ..
	//{
	//	if (dwReadBytes == 0 ||
	//		GetLastError() == ERROR_HANDLE_EOF)
	//	{
	//		return false;
	//	}
	//}
	return true;
}
void TIocp::Frame()
{
	//WaitForMultipleObjects(MAX_WORK_THREAD,m_hWorkThread,TRUE,1); // 1�� ������ Ÿ�� �ƿ��� �ɸ���.
	
	WaitForRead();
	
	while(WaitForMultipleObjects(MAX_WORK_THREAD, m_hWorkThread, TRUE, 1));
	Release();
}


void Main()
{
	TIocp iocp;
	iocp.Init();
	iocp.Frame();
	_getch();
}