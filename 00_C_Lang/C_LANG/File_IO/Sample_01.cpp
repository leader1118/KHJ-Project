#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main()
{
	int iValue = 50; //���� 2��
	float fValue = 3.141592f;
	FILE* fp = fopen("demo.txt", "w"); //���� ������ ��� ���� �ִ� ������Ʈ ������"demo.txt"��� ���� w==���� ���� ���� ��쿡 ���� ���� ���
	{
		fprintf(fp, "%s", "============ KGCA ==========");
		fprintf(fp, "\n%s", "ȫ�浿");
		fprintf(fp, "%d %f", iValue,fValue);
		fclose(fp);
	}
	iValue = 99;
	fValue = 6.26f;
	fp = fopen("demo.txt", "a");
	{
		fprintf(fp,"\n%s", "������");
		fprintf(fp, "%d %f", iValue, fValue);
		fclose(fp);
	}

	char buffer[256] = { 0, };
	int iValueRead;
	float fValueRead;

	FILE* fpRead = fopen("demo.txt", "r");
	{
		fgets(buffer, 256,fpRead);
		fscanf(fpRead, "%s %d %f", buffer, &iValueRead, &fValueRead);
		printf("\n%s %d %f", buffer, iValueRead, fValueRead);
		fscanf(fpRead, "%s %d %f", buffer, &iValueRead, &fValueRead);
		printf("\n%s %d %f", buffer, iValueRead, fValueRead);
		fclose(fpRead);
	}
	_getch();
	return 0;
}