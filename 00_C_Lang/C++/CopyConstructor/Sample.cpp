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
	//explicit�� ������ �տ� �ٿ��� �������� ȣ���� �����Ѵ�.
	//�̴� ������� ȣ�⸸ ������� �Ѵ�.
	explicit TClassExplicit(int iValue) :m_iValue(iValue)
	{

	}
	//explicit�� ���� �����ڿ��� ����ϸ�
	// ���� �����ڸ� ���Ͽ� ��ü�� ���� �� �ʱ�ȭ�� �� �� ����.
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
	//mutable �� const �Լ����� ���氡���� ����.
	//�̴� constdml ���ܸ� �δ� ����� �ȴ�.
	mutable int m_iData;
public:
	// �Լ��� const ������ mutable�� ���� ������ ���������� ����Ѵ�.
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
	// ������ ��ȯ�� �߻����� ���Ѵ�.
	//TClassExplicit tE=3;//Error

	// ���� �����ڸ� ���Ͽ� ��ü�� ���� �� �ʱ�ȭ�� �� �� ����.
	//TClassExplicit tF=tD//Error
	TClassExplicit pColp(tD);//oK

	TClassMutable tG(3);
	cout << tG.Get(5);
}