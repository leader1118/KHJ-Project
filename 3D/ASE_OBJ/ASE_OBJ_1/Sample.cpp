#pragma once
#include "xCore.h"
#include "x_AseMesh.h"

class Sample : public x_AseMesh
{
public:

	x_AseMesh m_Obj;
public:
	bool Init()
	{
		return m_Obj.Load();
	}
public:
	Sample() {};
	virtual~Sample() {};
}