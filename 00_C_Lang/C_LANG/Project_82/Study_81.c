#include<stdio.h>
//시계 예제
void main()
{
	int hour = 0;
	int sec = 0;
	int min = 0;
	int j = 0;

	for (sec = 1; sec <= 100; sec++)
	{
		printf("%3d:%3d:%3d", hour, min, sec);

		for (j = 1; j < 55000000; j++)
		{
			for (int k = 0; k < 20; k++)
			{
				putchar('\010');
			}
			if (sec > 60)
			{
				sec = 0;
				if (min > 60)
				{
					hour++;
					min = 0;
				}
				else
				{
					min++;
				}
			}
		}
	}
}