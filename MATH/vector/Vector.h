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
	Vector2(const Vector2& vO); // ���� ������
	Vector2(float fX, float fY);
	~Vector2() {}
};

class Vector3 : public float3
{
public:
	Vector3();
	Vector3(const Vector3& vO);
	Vector3(float fX, float fY, float fZ);

	// ������ ������
	Vector3 operator + (Vector3 const &vO);
	Vector3 operator - (Vector3 const &vO);
	Vector3 operator * (float const &fScala);
	Vector3 operator + (float const &fScala);
	Vector3 operator / (float const &fScala);
	bool	operator == (Vector3 const &vO);
	
	// ���� ����
	float operator | (Vector3 const& vO);
	Vector3 operator ^ (Vector3 const& vO);

	// ����
	float LengthSquared();

	// �������� ������ �Ÿ�
	float Length();
	
	Vector3 Normalize(); // ����ȭ
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