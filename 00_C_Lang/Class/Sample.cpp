#include"TPoint.h"

int main(void)
{
	TPoint p1, p2; //���� ��ǥ�� ������ ���� ����

	p1.SetPosition(10, 20); //p1�� ��ǥ ����
	p2.SetPosition(50, 60); //p2�� ��ǥ����

	p1.Move(5, 0); //p1�� ��ǥ �̵�
	p2.Move(0, 5); //p2�� ��ǥ �̵�

	p1.Show(); //p1�� ��ǥ�� ���
	p2.Show(); //p2�� ��ǥ�� ���

	_getch();
	return 0;
}