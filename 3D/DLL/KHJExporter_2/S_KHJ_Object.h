#pragma once
#include "S_KHJ_Global.h"

class S_KHJ_Object : public S_KHJ_Global
{
public:
	void GetMaterial(); // ���͸��� ����Ʈ���� ���� ���
	void GetTexture(SMtl* pDestMtl, Mtl* pSrcMtl); // ���͸��� ����Ʈ���� �������
public:
	void UpdateObject();
	void GetObject(MATRIXINDEX* pPoint); // ������Ʈ ����Ʈ���� �������
	// ������Ʈ ����
	void GetNodeheader(INode* node, SMesh* pMesh);
	void GetNodeTM(INode* node, SMesh* pMesh);
	// �޽� ����
	void GetMesh(INode* node, SMesh* pMesh);
	Point3 GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv);
	TriObject* GetTriObjectFromNode(INode* node, TimeValue t, int & deletelt);
	// �ִϸ��̼�
	virtual void GetAnimKeys(INode*, SMesh*) {};
public:
	S_KHJ_Object(void);
	virtual ~S_KHJ_Object(void);
};

