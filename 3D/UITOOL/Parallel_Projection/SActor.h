#pragma once
#include "sDxObj.h"


struct _DX_MATRIX
{
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23,_24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

struct DX_MATRIX : public _DX_MATRIX
{
	void RoationX(float fAngle)
	{
		_22 = cosf(fAngle);
		_23 = sinf(fAngle);
		_32 = -sinf(fAngle);
		_33 = cosf(fAngle);
	}

	void RoationY(float fAngle)
	{
		_11 = cosf(fAngle);
		_13 = -sinf(fAngle);
		_31 = sinf(fAngle);
		_33 = cosf(fAngle);
	}
	void RoationZ(float fAngle)
	{
		_11 = cosf(fAngle);
		_12 = sinf(fAngle);
		_21 = -sinf(fAngle);
		_22 = cosf(fAngle);
	}
	void Indentity(float fAngle)
	{
		_11 = 1.0f; _21 = 0.0f; _31 = 0.0f; _41 = 0.0f;
		_12 = 0.0f; _22 = 1.0f; _32 = 0.0f; _42 = 0.0f;
		_13 = 0.0f; _23 = 0.0f; _33 = 1.0f; _43 = 0.0f;
		_14 = 0.0f; _24 = 0.0f; _34 = 0.0f; _44 = 1.0f;
	}
	void Transpose()
	{
		DX_MATRIX mat = *this;
		mat._11 = _11; mat._12 = _21; mat._13 = _31; mat._14 = _41;
		mat._21 = _12; mat._22 = _22; mat._23 = _32; mat._24 = _42;
		mat._31 = _13; mat._32 = _23; mat._33 = _33; mat._34 = _43;
		mat._41 = _14; mat._42 = _24; mat._43 = _34; mat._44 = _44;
		*this = mat;
	}
	DX_MATRIX()
	{
		_11 = _22 = _33 = _44 = 1.0f;
		_12 = _13 = _14 = 0.0f;
		_21 = _23 = _24 = 0.0f;
		_31 = _32 = _34 = 0.0f;
		_41 = _42 = _43 = 0.0f;
	}

};

struct SActorCB
{
	DX_MATRIX m_matWorld;
	DX_MATRIX m_matView;
	DX_MATRIX m_matProj;
};

struct SOffSet
{
	float fScaleX0;
	float fScaleX1;
	float fScaleY0;
	float fScaleY1;
	float fOffsetU0;
	float fOffsetV0;
	float fOffsetU1;
	float fOffsetV1;
};

struct SPoint
{
	float x, y;
};

class SActor
{
public:
	RECT m_rtInit;
	SOffSet m_sOffset;
	PNCT_VERTEX m_VertexList[6];
public:
	sDxObj m_dxObj;
	D3DXVECTOR3 m_vCenter;
	SActorCB m_ActorCB;
public:
	virtual bool Init();
	virtual bool Frame(float fGameTimer, float fFps);
	virtual bool PreRender(ID3D11DeviceContext* pContext, UINT iVertexSize);
	virtual bool Render(ID3D11DeviceContext* pContext, UINT iVertexSize, UINT iCount);
	virtual bool PostRender(ID3D11DeviceContext* pContext, UINT iVertexSize, UINT iCount);
	virtual bool Release();
public:
	virtual D3DXVECTOR3 Gen(float x, float y);
	virtual void GenCenter();
	virtual void SetVertexData();
	virtual bool Setdata(UINT left, UINT top, UINT width, UINT height);
public:
	SActor();
	virtual ~SActor();
};

