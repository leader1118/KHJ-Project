#include <iostream>

int g_iArray[10][10];
unsigned short Hash(void* p)
{
	unsigned short val = reinterpret_cast<unsigned short>(p);
	return val % 10;
}
void Set(int iRow, int iValue)
{
	for (int i = 0; i < 10; i++)
	{
		if (g_iArray[iRow][i] <= 0)
		{
			g_iArray[iRow][i] = iValue;
			break;
		}
	}
}
int Get(int iRow, int iValue)
{
	for (int i = 0; i < 10; i++)
	{
		if (g_iArray[iRow][i] == iValue)
		{
			return g_iArray[iRow][i];
		}
	}
	return -1;
}
int main()
{
	int iArray[100];
	for (int i = 0; i < 10; i++)
	{
		iArray[i] = i + 1;
		unsigned short iHash =
			Hash(&iArray[i]);
		std::cout <<
			Get(iHash, iArray[i]) << " " << std::endl;
	}
	return 0;
}