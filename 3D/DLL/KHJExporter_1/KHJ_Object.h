#pragma once
#include "KHJ_Global.h"

class KHJ_Object : public KHJ_Global
{
public:
	void GetMaterial(); // ���͸��� ����Ʈ���� ���� ���
	void GetTexture(SMtl* pDestMtl, Mtl* pSrcMtl); // ���͸��� ����Ʈ���� �������
public:
	void UpdateObject();
	void GetObject(MATRIXINDEX* pPoint); // ������Ʈ ����Ʈ���� �������
	// ������Ʈ ����
	void GetNodeHeader(INode* node, SMesh* pMesh);
	void GetNodeTM(INode* node, SMesh* pMesh);
	// �޽� ����
	void GetMesh(INode* node, SMesh* pMesh);
	Point3 GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv);
	TriObject* GetTriObjectFromNode(INode* node, TimeValue t, int & deletelt);
	// �ִϸ��̼�
	virtual void GetAnimKeys(INode*, SMesh*) {};
public:
	KHJ_Object(void);
	virtual ~KHJ_Object(void);
};

