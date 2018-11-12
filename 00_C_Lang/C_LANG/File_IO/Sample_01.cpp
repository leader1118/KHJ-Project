#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main()
{
	int iValue = 50; //변수 2개
	float fValue = 3.141592f;
	FILE* fp = fopen("demo.txt", "w"); //파일 포인터 사용 현재 있는 프로젝트 폴더에"demo.txt"라는 것을 w==쓰기 파일 없는 경우에 파일 만들어서 써라
	{
		fprintf(fp, "%s", "============ KGCA ==========");
		fprintf(fp, "\n%s", "홍길동");
		fprintf(fp, "%d %f", iValue,fValue);
		fclose(fp);
	}
	iValue = 99;
	fValue = 6.26f;
	fp = fopen("demo.txt", "a");
	{
		fprintf(fp,"\n%s", "개똥이");
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