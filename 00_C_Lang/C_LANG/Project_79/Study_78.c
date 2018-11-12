#include<stdio.h>
#include<conio.h>
//Á¦¾î¹®

//void main()
//{
//	int oddTotal = 0;
//	int evenTotal = 0;
//
//	for (int i = 1; i <= 100; i++)
//	{
//		if (i % 2 == 0)
//		{
//			evenTotal += i;
//		}
//		else
//		{
//			oddTotal += i;
//		}
//	}
//	printf("%d%d", evenTotal, oddTotal);
//}

int get_menu_choice(void);
void main()
{
	int choice;
	choice = get_menu_choice();
	printf("You chose Menu Option %d\n", choice);
}
int get_menu_choice()
{
	int selection = 0;
	do
	{
		printf("1.Add aRecord\n");
		printf("2.Change a record\n");
		printf("3.Quit\n");
		printf("1. Enter Selection:");
		scanf_s("%d", &selection);
	} while (selection < 1 || selection>3);
	return selection;
}