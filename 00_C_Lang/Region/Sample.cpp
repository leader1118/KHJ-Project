#include "TRegion.h"
int main(void)
{
	TRegion::SetNotation(TRegion::POINT_POINT);	// ��� ���� ����
	TRegion r1(10, 10, 100, 100);		// ���� r1 ����
	TRegion r2(50, 50, 120, 120);		// ���� r2 ����

										////////////////////  ��� ��ü ��ȯ ////////////////////////
	const TRegion* x1 = r1.Get();
	const TRegion& x2 = r2.GetRef();
	//TRegion* x1 = r1.Get();		// ����!  ���� ������
	//TRegion& x2 = r2.GetRef();	// ����!  ���� ����
	int iX = x1->GetWidth();		// ����!  �� ��� ��ȯ & ��� �Լ� ȣ��
	int iT = x1->GetHeight();		// ����!  ��� ��ȯ & ��� �Լ� ȣ��
	const int iC = x1->GetWidth();	// ����!  �� ��� ��ȯ & ��� �Լ� ȣ��
	const int iD = x1->GetHeight();	// ����!  ��� ��ȯ & ��� �Լ� ȣ��
									//int iValue = x1->GetLeft();	// ����!  ���� �Լ� ȣ��
	int iXref = x2.GetWidth();		// ����!  ��� �Լ� ȣ��
									//int iValueref = x2.GetLeft(); // ����!  ���� �Լ� ȣ��
									///////////////////  ��� ������ ��ȯ ///////////////////////	
	int iY = r1.GetLeft();			// ����! �� ��� ��ȯ �Լ� ȣ��
	int iZ = r1.GetTop();			// ����! ��� ��ȯ �Լ� ȣ��
	const int iG = r1.GetLeft();	// ����! �� ��� ��ȯ �Լ� ȣ��
	const int iJ = r1.GetTop();		// ����! ��� ��ȯ �Լ� ȣ��
									//int* iP = r1.GetRight();		// ����! ��� ��ȯ �Լ� ȣ��
	const int* iQ = r1.GetRight();	// ����! ��� ��ȯ �Լ� ȣ��	
									//int& i6 = r1.GetBottom();     // ����! ��� ��ȯ �Լ� ȣ��
	const int& i7 = r1.GetBottom(); // ����! ��� ��ȯ �Լ� ȣ��

									///////////////////  ���� ���� �Լ� ///////////////////////	
	TRegion r3;
	// r1�� r2�� �������� r3�� ����
	r3.IntersectRegion(r1, r2);	r3.Show();
	// r1�� r2�� �������� r3�� ����
	r3.UnionRegion(r1, r2);		r3.Show();
	// r3�� ��ġ �̵�
	r3.Move(100, 100);			r3.Show();
	// r3�� ũ�� ����
	r3.Resize(200, 200);		r3.Show();

	TRegion::SetNotation(TRegion::POINT_SIZE);	// ��� ���� ����
	r1.Show();
	r2.Show();
	r3.Show();
	return 0;
}
