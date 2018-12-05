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


template<class T> class Singleton
{
public:
	static T& GetInstance()
	{
		static T theSingleInstance;
		return theSingleInstance;
	}
};

#define SAFE_NEW(A, B)	{ if (!A) A = new B; }
#define SAFE_DELETE(p) if(p){delete p; p = NULL;}

extern HWND g_hWnd;