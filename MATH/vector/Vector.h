#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>


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

class Vector3 : public float3
{
public:
	Vector3();
	Vector3(const Vector3& vO);
	Vector3(float fX, float fY, float fZ);

	// 연산자 재정의
	Vector3 operator + (Vector3 const &vO);
	Vector3 operator - (Vector3 const &vO);
	Vector3 operator * (float const &fScala);
	Vector3 operator + (float const &fScala);
	Vector3 operator / (float const &fScala);
	bool	operator == (Vector3 const &vO);
	
	// 내적 외적
	float operator | (Vector3 const& vO);
	Vector3 operator ^ (Vector3 const& vO);

	// 제곱
	float LengthSquared();

	// 원점으로 부터의 거리
	float Length();
	
	Vector3 Normalize(); // 정규화
	Vector3 Normal();
	~Vector3() {}
};

class Vector4 : public float4
{
public:
	Vector4();
	Vector4(const Vector4& vO);
	Vector4(float fX, float fY, float fZ, float fW);
	~Vector4() {}
};