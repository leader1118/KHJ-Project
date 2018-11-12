#include "DXVector.h"

D3DXVECTOR3::D3DXVECTOR3()
{
	x = y = z = 0.0f;
}
D3DXVECTOR3::D3DXVECTOR3(const D3DXVECTOR3& vO)
{
	x = vO.x;
	y = vO.y;
	z = vO.z;
}
D3DXVECTOR3::D3DXVECTOR3(float fX, float fY, float fZ)
{
	x = fX;
	y = fY;
	z = fZ;
}




// 연산자 재정의

D3DXVECTOR3 D3DXVECTOR3::operator + (D3DXVECTOR3 const &vO)
{
	return D3DXVECTOR3(
		vO.x + x,
		vO.y + y,
		vO.z + z);
}

D3DXVECTOR3 D3DXVECTOR3::operator - (D3DXVECTOR3 const &vO)
{
	return D3DXVECTOR3(
		x - vO.x,
		y - vO.y,
		z - vO.z);
}

D3DXVECTOR3 D3DXVECTOR3::operator + (float const &fScala)
{
	return D3DXVECTOR3(
		fScala + x,
		fScala + y,
		fScala + z);
}

D3DXVECTOR3 D3DXVECTOR3::operator * (float const &fScala)
{
	return D3DXVECTOR3(
		fScala*x,
		fScala*y,
		fScala*z);
}

D3DXVECTOR3 D3DXVECTOR3::operator / (float const &fScala)
{
	float fInvert = 1.0f / fScala;
	return D3DXVECTOR3(
		x*fInvert,
		y*fInvert,
		z*fInvert);
}

bool D3DXVECTOR3::operator == (D3DXVECTOR3 const &vO) //fabs == 절대값
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

float D3DXVECTOR3::LengthSquared()
{
	return (x*x + y * y + z * z);
}

// 원점으로 부터의 거리

float D3DXVECTOR3::Length()
{
	return (float)sqrt(LengthSquared());
}

D3DXVECTOR3 D3DXVECTOR3::Normalize() // 정규화
{
	float invertLength = 1.0f / Length();
	return D3DXVECTOR3(
		x*invertLength,
		y*invertLength,
		z*invertLength);
}

D3DXVECTOR3 D3DXVECTOR3::Normal()
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
float D3DXVECTOR3 :: operator | (D3DXVECTOR3 const & vO)
{
	return x * vO.x + y * vO.y + z * vO.z;
}
D3DXVECTOR3 D3DXVECTOR3::operator ^(D3DXVECTOR3 const& vO)
{
	return D3DXVECTOR3((y*vO.z - z * vO.y),
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