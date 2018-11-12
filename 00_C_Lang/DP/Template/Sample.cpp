#include <iostream>

using namespace std;

template<typename D>
void Swap(D& Num, D& Count)
{
	D temp = Num;
	Num = Count;
	Count = temp;
}
int main()
{
	int Num = 10, Count = 40;
	cout << " Num:" << Num << ", Count" << Count << endl;
	Swap(Num, Count);
	cout << "swap Num: " << Num << ", Count " << Count << endl;

	system("pause");
}