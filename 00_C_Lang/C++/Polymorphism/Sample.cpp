#include "TDepartment.h"

int main()
{
	//������ �����ϴ� CONTROL Ŭ����
	TDepartment department;
	//���� ���
	department.AddEmployee(new TPermanent("KIM", 1000));
	department.AddEmployee(new TPermanent("LEE", 1500));
	department.AddEmployee(new TTemporary("HAN", 10, 200));
	department.AddEmployee(new TTemporary("JANG", 12, 300));
	//���������� �̹��޿� �����ؾ��� �޿���?
	department.ShowList();
	return 0;
}