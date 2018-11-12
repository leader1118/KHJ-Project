#pragma once
#include "DDefine.h"

namespace TBASIS_BASE
{
	template<class D> class DSingleton
	{
	public:
		static D& GetInstance()
		{
			static D theSingleInstance;
			return theSingleInstance;
		}
		static D* GetInstancePtr()
		{
			static D theSingleInstance;
			return &theSingleInstance;
		}
	};
}