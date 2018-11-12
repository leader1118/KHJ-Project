#include <iostream>
template <typename T>
void swap(T &a,T &b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;	
}

int main(void)
{
	int a = 1, b = 2;
	swap(a, b);
	std::cout << a << "," << b << std::endl;

	double c = 0.1, d = 0.2;
	swap(c, d);
	std::cout << c << "," << d << std::endl;
	return 0;
}