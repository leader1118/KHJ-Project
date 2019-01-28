#pragma once
#include "S_CharMgr.h"

#define MAX_BONE_MATRICES 255

struct CBConstBoneWorld
{
	D3DXMATRIX g_mConstBoneWorld[MAX_BONE_MATRICES];
};

class S_HeroObj
{
public:
	S_HeroObj();
	virtual ~S_HeroObj();
};

