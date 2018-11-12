#pragma once
#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>
#include <d3dx10math.h>
#pragma comment(lib,"d3dx10.lib")


//#include <wrl.h> 윈도우 런타임 라이브러리
//using namespace Microsoft::WRL; 
//ComPtr<ID3D11Buffer> 변수 Release 안해도 된다 이렇게 하면



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
	Vector2(const Vector2& vO); // 복사 생성자
	Vector2(float fX, float fY);
	~Vector2() {}
};

class D3DXVECTOR3 : public float3
{
public:
	D3DXVECTOR3();
	D3DXVECTOR3(const D3DXVECTOR3& vO);
	D3DXVECTOR3(float fX, float fY, float fZ);

	// 연산자 재정의
	D3DXVECTOR3 operator + (D3DXVECTOR3 const &vO);
	D3DXVECTOR3 operator - (D3DXVECTOR3 const &vO);
	D3DXVECTOR3 operator * (float const &fScala);
	D3DXVECTOR3 operator + (float const &fScala);
	D3DXVECTOR3 operator / (float const &fScala);
	bool	operator == (D3DXVECTOR3 const &vO);

	// 내적 외적
	float operator | (D3DXVECTOR3 const& vO);
	D3DXVECTOR3 operator ^ (D3DXVECTOR3 const& vO);

	// 제곱
	float LengthSquared();

	// 원점으로 부터의 거리
	float Length();

	D3DXVECTOR3 Normalize(); // 정규화
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



// 내적
//float fDot = D3DXVec3Dot(a, b);
// 외적
//D3DXVECTOR3 vRet = D3DXVec3Cross(ret, a, b);