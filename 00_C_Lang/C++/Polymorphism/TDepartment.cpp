#include "TDepartment.h"
void TDepartment::AddEmployee(TEmployee* emp)
{
	empList[index++] = emp;
}
void TDepartment::ShowList()//급여리스트 출력
{
	for (int i = 0; i < index; i++)
	{
		cout << "name: " << empList[i]->GetName() << endl;
		cout << "salary: " << empList[i]->GetPay() << endl;
		cout << endl;
	}
}



