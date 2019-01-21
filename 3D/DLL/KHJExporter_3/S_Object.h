#pragma once
#include "S_Global.h"

class S_Object : public S_Global
{
public:
	void GetMaterial();
	void GetTexture(SMtl* pDestMtl, Mtl* pSrcMtl);
public:
	void UpdateObject();
	void GetObject(MATRIXINDEX* pPoint);

	void GetNodeHeader(INode* node, SMesh* pMesh);
	void GetNodeTM(INode* node, SMesh* pMesh);

	void GetMesh(INode* node, SMesh* pMesh);
	Point3 GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv);
	TriObject* GetTriObjectFromNode(INode* node, TimeValue t, int &deletelt);

	virtual void GetAnimKeys(INode*, SMesh*) {};
public:
	S_Object(void);
	virtual ~S_Object(void);
};

