#pragma once
#include "DG_Shape.h"
class ViewCube :public DG_Shape
{
public:
	bool CreateVertexData();
	bool CreateIndexData();
	HRESULT CreateResource();
public:
	ViewCube();
	virtual ~ViewCube();
};

