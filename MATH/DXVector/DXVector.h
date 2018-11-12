#pragma once
#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>
#include <d3dx10math.h>
#pragma comment(lib,"d3dx10.lib")


//#include <wrl.h> ������ ��Ÿ�� ���̺귯��
//using namespace Microsoft::WRL; 
//ComPtr<ID3D11Buffer> ���� Release ���ص� �ȴ� �̷��� �ϸ�



#define TBASIS_EPSILON ((FLOAT)  0.001f) 
#define TBASIS_PI 3.141592654
#define DtoR(degree) ((degree)*(TBASIS_PI/180.0))
#define RtoD(radian) ((radian)*(180.0/TBASIS_PI))

struct float2
{
	union
	{
		struct { float x, y; };
		float v[2];
	};
};
struct float3
{
	union
	{
		struct { float x, y, z; };
		float v[3];
	};
};
struct float4
{
	union
	{
		struct { float x, y, z, w; };
		float v[4];
	};
};


class Vector2 : public float2
{
public:
	bool operator | (Vector2 const & vO);
	Vector2 operator ^ (Vector2 const& vO);

public:
	Vector2();
	Vector2(const Vector2& vO); // ���� ������
	Vector2(float fX, float fY);
	~Vector2() {}
};

class D3DXVECTOR3 : public float3
{
public:
	D3DXVECTOR3();
	D3DXVECTOR3(const D3DXVECTOR3& vO);
	D3DXVECTOR3(float fX, float fY, float fZ);

	// ������ ������
	D3DXVECTOR3 operator + (D3DXVECTOR3 const &vO);
	D3DXVECTOR3 operator - (D3DXVECTOR3 const &vO);
	D3DXVECTOR3 operator * (float const &fScala);
	D3DXVECTOR3 operator + (float const &fScala);
	D3DXVECTOR3 operator / (float const &fScala);
	bool	operator == (D3DXVECTOR3 const &vO);

	// ���� ����
	float operator | (D3DXVECTOR3 const& vO);
	D3DXVECTOR3 operator ^ (D3DXVECTOR3 const& vO);

	// ����
	float LengthSquared();

	// �������� ������ �Ÿ�
	float Length();

	D3DXVECTOR3 Normalize(); // ����ȭ
	D3DXVECTOR3 Normal();
	~D3DXVECTOR3() {}
};

class Vector4 : public float4
{
public:
	Vector4();
	Vector4(const Vector4& vO);
	Vector4(float fX, float fY, float fZ, float fW);
	~Vector4() {}
};



// ����
//float fDot = D3DXVec3Dot(a, b);
// ����
//D3DXVECTOR3 vRet = D3DXVec3Cross(ret, a, b);