#include<iostream>
#include<conio.h>

using namespace std;
class CCTest
{
public:
	void setNumber(int);
	void printNumber()const;
	const int* GetConst();
private:
	int number;
};

void CCTest::setNumber(int num) { number = num; }
//��� �Լ�const�� ������ Ŭ���� ��ü�� ���ȭ�ȴ�.
void CCTest::printNumber()const
{
	cout << "\nBefore: " << number;
	const_cast<CCTest *>(this)->number--;
	cout << "\nAfter: " << number;
}
const int* CCTest::GetConst()
{
	return&number;
}
int main()
{
	CCTest X;
	X.setNumber(8);

	//1
	const int* iValue = X.GetConst();
	//*iValue=20; //�������
	//2
	int* iValue2 = const_cast<int*>(X.GetConst());
	*iValue2 = 20;

	X.printNumber();
	_getch();
}