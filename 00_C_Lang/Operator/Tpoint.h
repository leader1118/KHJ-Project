#pragma once
#include <iostream>
using namespace std;
//const char& operator []() const {}
//char& operator []() 두 함수는 별개의 함수가 된다.

// 연산자 재정의 불가
//1)선택 연산자: .
//2)포인터 선택 연산자: .*
//3)영역 연산자: ::
//4)조건 연산자: ? :
//5)크기 연산자: sizeof
class Tpoint
{
public:
	int x, y;
	void SetPosition(int _x, int _y);
	void Move(int _x, int _y);
	void Show(void);
public:
	Tpoint * operator->()
	{
		return this;
	}
	Tpoint& operator*()
	{
		return *this;
	}
	Tpoint operator++(void);//++p1
	Tpoint operator++(int);//p1--
	//이항연산자 p3=p1+p2;
	Tpoint operator+(const Tpoint &pt)const;
	Tpoint operator-(const Tpoint &pt)const;
	Tpoint operator*(const Tpoint &c);
	Tpoint operator/(const Tpoint &c);

	Tpoint operator*(int mag)const; //p2=p1*2;
	Tpoint operator/(int div)const; //p2=p1/2;

	friend Tpoint operator*(int mag, const Tpoint &pt);// p2=2*p1
	friend Tpoint operator/(int div, const Tpoint &pt);//p2=2/p1

	Tpoint &operator=(const Tpoint &pt);
	Tpoint &operator+=(const Tpoint &pt);
	Tpoint &operator-=(const Tpoint &pt);
	Tpoint &operator*=(const Tpoint &pt);
	Tpoint &operator/=(const Tpoint &pt);
	Tpoint &operator*= (int mag);
	Tpoint &operator/=(int div);

	bool operator ==(const Tpoint &pt)const;
	bool operator !=(const Tpoint &pt)const;

	int &operator[](int index);
	void *operator new(size_t size);
	void operator delete(void *p);

	//std::cout<<*pFindA<<*pFindB;
	friend ostream &operator <<(ostream &os, const Tpoint &pt);
	friend istream &operator >>(istream& is, Tpoint &pt);

	void (Tpoint::*m_fp)();
	void Execute()
	{
		if (m_fp != NULL)
		{
			(this->*m_fp)();
		}
	}
	void operator >(Tpoint* the)
	{
		if (m_fp != NULL)
		{
			(the->*m_fp)();
		}
	}
public:
	Tpoint();
	Tpoint(int x, int y);
	~Tpoint();
};

