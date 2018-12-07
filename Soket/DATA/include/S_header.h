#include "S_Std.h"
typedef struct _OVERLAPPEDEX : OVERLAPPED
{
	enum {MODE_RECV = 0 , MODE_SEND = 1};
	int i_Flags;
	_OVERLAPPEDEX()
	{
		i_Flags = MODE_RECV;
	}
}OVERLAPPEDEX;


template <class S> class Singleton
{
public:
	static S& GetInstance()
	{
		static S theSingleInstance;
		return theSingleInstance;
	}
};
#define MAX_ARRAY 256
#define SAFE_NEW(A, B)	{ if (!A) A = new B; }
#define SAFE_DELETE(p) if(p){delete p; p = NULL;}
#define PACKETBUFFERSIZE 8192
#define MAX_RECV 10000
extern HWND g_hWnd;