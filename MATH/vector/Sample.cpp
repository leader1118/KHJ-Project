#include "Vector.h"

Vector3::Vector3()
{
	x = y = z = 0.0f;
}
Vector3::Vector3(const Vector3& vO)
{
	x = vO.x;
	y = vO.y;
	z = vO.z;
}
Vector3::Vector3(float fX, float fY, float fZ)
{
	x = fX;
	y = fY;
	z = fZ;
}




// 연산자 재정의

Vector3 Vector3::operator + (Vector3 const &vO)
{
	return Vector3(
		vO.x + x, 
		vO.y + y, 
		vO.z + z);
}

Vector3 Vector3::operator - (Vector3 const &vO)
{
	return Vector3(
		x - vO.x, 
		y - vO.y, 
		z - vO.z);
}

Vector3 Vector3::operator + (float const &fScala)
{
	return Vector3(
		fScala + x, 
		fScala + y, 
		fScala + z);
}

Vector3 Vector3::operator * (float const &fScala)
{
	return Vector3(
		fScala*x, 
		fScala*y, 
		fScala*z);
}

Vector3 Vector3::operator / (float const &fScala)
{
	float fInvert = 1.0f / fScala;
	return Vector3(
		x*fInvert, 
		y*fInvert,
		z*fInvert);
}

bool Vector3::operator == (Vector3 const &vO) //fabs == 절대값
{
	if (fabs(x - vO.x) < TBASIS_EPSILON)
	{
		if (fabs(y - vO.y) < TBASIS_EPSILON)
		{
			if (fabs(z - vO.z) < TBASIS_EPSILON)
			{
				return true;
			}
		}
	}
	return false;
}

// 제곱

float Vector3::LengthSquared()
{
	return (x*x + y * y + z * z);
}

// 원점으로 부터의 거리

float Vector3::Length()
{
	return (float)sqrt(LengthSquared());
}

Vector3 Vector3::Normalize() // 정규화
{
	float invertLength = 1.0f / Length();
	return Vector3(
		x*invertLength,
		y*invertLength,
		z*invertLength);
}

Vector3 Vector3::Normal()
{
	if (Length() - 0.0f, 0.001f)
	{
		return *this;
	}
	float invertLength = 1.0f / Length();
	x *= invertLength;
	y *= invertLength;
	z *= invertLength;
	return *this;
}

// 3D 내적 외적
float Vector3 :: operator | (Vector3 const & vO)
{
	return x * vO.x + y * vO.y + z * vO.z;
}
Vector3 Vector3::operator ^(Vector3 const& vO)
{
	return Vector3((y*vO.z - z * vO.y), 
		(z*vO.x - x * vO.z), 
		(x*vO.y - y * vO.x));
}





// Vector2
Vector2::Vector2()
{
	x = y = 0.0f;
}

Vector2::Vector2(const Vector2& vO)
{
	x = vO.x;
	y = vO.y;
}

Vector2::Vector2(float fX, float fY)
{
	x = fX;
	y = fY;
}

// 2D 내적 외적
bool Vector2::operator | (Vector2 const & vO)
{
	return x * vO.x + y * vO.y;
}
Vector2 Vector2::operator ^ (Vector2 const& vO)
{
	return Vector2(0, (x*vO.y - y * vO.x));
}






// Vector4
Vector4::Vector4()
{
	x = y = z = w = 0.0f;
}

Vector4::Vector4(const Vector4& vO)
{
	x = vO.x;
	y = vO.y;
	z = vO.z;
	w = vO.w;
}

Vector4::Vector4(float fX, float fY, float fZ, float fW)
{
	x = fX;
	y = fY;
	z = fZ;
	w = fW;
}

void main()
{

}