#pragma once


typedef basic_string<TCHAR> T_STR;
typedef basic_string<CHAR>  C_STR;

template <class S> class SSingleton
{
public:
	static S& GetInstance()
	{
		static S theSingleInstance;
		return theSingleInstance;
	}
};