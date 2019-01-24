#pragma once
#include "S_Object.h"

class S_AnimObj :public S_Object
{
public:
	int m_iDeltatick;
public:
	void GetAnimKeys(INode* pNode, SMesh* pMesh);
	void DumpScaleSample(INode* pNode, SMesh* pMesh);
	void DumpRotSample(INode* pNode, SMesh* pMesh);
	void DumpPosSample(INode* pNode, SMesh* pMesh);
	BOOL CheckForAnimation(INode* pNode, BOOL& bPos, BOOL& bRot, BOOL& bScale);
	bool GetDecompAffine(TimeValue t, INode* pNode, AffineParts* ap,
		Point3* rotAxis = NULL, float* rotAngle = NULL);
public:
	void DumpFloatKeys(Control* cont, SMesh* pMesh);
public:
	S_AnimObj(void);
	virtual ~S_AnimObj(void);
};

