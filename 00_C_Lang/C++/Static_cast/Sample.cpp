#include <iostream>
using namespace std;
//static_cast 의미없는 형변환 방지.
typedef unsigned char BYTE;

void f()
{
	char ch;
	int i = 65;
	float f = 2.5;
	double dbl;

	ch = static_cast<char>(i); //int to char
	dbl = static_cast<double>(f); //float to double
	i = static_cast<BYTE>(ch);
}

class B
{
public:
	virtual void Test(){}
};
class D :public B{};// 상속

void f(B* pb)
{
	D* pd1 = dynamic_cast<D*>(pb);
	D*pd2 = static_cast<D*>(pb);
	if (pd1 == NULL)
		cout << "pd1==NULL" << endl;
	else
		cout << "pd1 !=NULL" << endl;
	if (pd2 == NULL)
		cout << " pd1 ==NULL" << endl;
	else
		cout << "pd1 != NULL" << endl;
}
void f2(B* pb, D* pd)
{
	D* pd2 = static_cast<D*>(pb); //안전하지 않다.
	B* pd2 = static_cast<B*>(pd); //안전하다.(safe conversion)
}
///////////////////////////////////////////////////////////////
class BClass;
class AClass
{
public:
	int m_iValue;
	operator BClass();
};
AClass::operator BClass()
{
	//멤버 초기화
	BClass fRet = { static_cast<float>(m_iValue) };
	return fRet;
};
class BClass
{
public:
	float m_fValue;
};
void main()
{
	f();
	B b;
	f(&b);
	//////////////////////////////////////////////////////
	AClass a;
	a.m_iValue = 99;
	BClass c;
	//static_cast는 형변환 방법을 알면 변환한다.
	//그러나 방법을 모르면 알려줘야 한다.
	c = static_cast<BClass>(a);
}