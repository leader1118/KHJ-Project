#include <iostream>
using namespace std;

class TClass
{
private:
	int m_iValue;
public:
	TClass(int iValue) :m_iValue(iValue)
	{

	}
	TClass(TClass& copy) : m_iValue(copy.m_iValue)
	{

	}
	~TClass(){}
};
class TClassExplicit
{
private:
	int m_iValue;
public:
	//explicit는 생성자 앞에 붙여서 묵시적인 호출을 방지한다.
	//이는 명시적인 호출만 가능토록 한다.
	explicit TClassExplicit(int iValue) :m_iValue(iValue)
	{

	}
	//explicit을 복사 생성자에서 사용하면
	// 대입 연산자를 통하여 객체의 생성 및 초기화를 할 수 없다.
	explicit TClassExplicit(TClassExplicit& copy);
	~TClassExplicit() {}
};
TClassExplicit::TClassExplicit(TClassExplicit& copy) : m_iValue(copy.m_iValue)
{
	//m_iValue=copy.m_ivalue;
}
class TClassMutable
{
private:
	int m_iValue;
	//mutable 은 const 함수에서 변경가능해 진다.
	//이는 constdml 예외를 두는 결과가 된다.
	mutable int m_iData;
public:
	// 함수가 const 이지만 mutable는 값의 변경을 예외적으로 허용한다.
	int Get(int iValue)const
	{
		m_iData = iValue;
		return m_iData;
	}
	explicit TClassMutable(int iVlaue) : m_iValue(iValue)
	{

	}
	explicit TClassMutable(TClassMutable& copy) :m_iValue(copy.m_iValue)
	{}
	TClassMutable(){}
};

void main()
{
	TClass tA(3);
	TClass tB = 3;
	TClass tC = tA;

	TClassExplicit tD(3);
	// 묵시적 변환이 발생하지 못한다.
	//TClassExplicit tE=3;//Error

	// 대입 연산자를 통하여 객체의 생성 및 초기화를 할 수 없다.
	//TClassExplicit tF=tD//Error
	TClassExplicit pColp(tD);//oK

	TClassMutable tG(3);
	cout << tG.Get(5);
}