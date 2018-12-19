#pragma once
#include "S_KHJ_Global.h"

class S_KHJ_Object : public S_KHJ_Global
{
public:
	void GetMaterial(); // 매터리얼 리스트에서 정보 얻기
	void GetTexture(SMtl* pDestMtl, Mtl* pSrcMtl); // 매터리얼 리스트에서 정보얻기
public:
	void UpdateObject();
	void GetObject(MATRIXINDEX* pPoint); // 오브젝트 리스트에서 정보얻기
	// 오브젝트 정보
	void GetNodeheader(INode* node, SMesh* pMesh);
	void GetNodeTM(INode* node, SMesh* pMesh);
	// 메쉬 정보
	void GetMesh(INode* node, SMesh* pMesh);
	Point3 GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv);
	TriObject* GetTriObjectFromNode(INode* node, TimeValue t, int & deletelt);
	// 애니메이션
	virtual void GetAnimKeys(INode*, SMesh*) {};
public:
	S_KHJ_Object(void);
	virtual ~S_KHJ_Object(void);
};

