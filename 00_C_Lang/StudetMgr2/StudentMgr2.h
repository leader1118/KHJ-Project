#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_SAVE_FILE 100
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<io.h>
#include<tchar.h>

typedef struct StudentNode// 구조체
{
	char strName[4];//구조체 멤버 변수
	int Index;
	int iKor;
	int iEng;
	int iMat;
	int Total;
	float Average;
}Student;//구조체 별칭

Student *pStudentData = 0;
int MaxCount = 0;
struct _finddata_t g_SaveFileArray[MAX_SAVE_FILE];
int g_MaxSaveFile = 0;

enum WORK//열거형
{
	NewData,
	PrintData,
	FindNameData,
	FindIndexData,
	SaveData,
	LoadData,
	AddData,
	DeleteData,
	EditData,
	Exit = 99,
};

void DataNew();
void DataPrint();
void DataFindIndex();
void DataFindName();
void DataSave();
void DataAdd();
void DataDelete();
void DataLoad();
void ReNumbering();
void DataEdit();
void FindFile();

void FindFile(void);
void SortFile(_finddata_t*c_file);


 void DataNew()//신규 데이터
{
	 printf("\n학생의 총 인원수를 입력하시오");
	 scanf("%d", &MaxCount);
	 if (pStudentData != NULL) 
	 {
		 free(pStudentData);
		 pStudentData = 0;
	 }
	 if (pStudentData == NULL)
	 {
		 pStudentData = (Student*)malloc(sizeof(Student)*MaxCount);
	 }
	 for (int i = 0; i < MaxCount; i++)
	 {
		 pStudentData[i].strName[0] = 65 + rand() % 26;
		 pStudentData[i].strName[1] = 65 + rand() % 26;
		 pStudentData[i].strName[2] = 65 + rand() % 26;
		 pStudentData[i].strName[3] = '\0';

		 pStudentData[i].Index = i;
		 pStudentData[i].iKor = rand() % 101;
		 pStudentData[i].iEng = rand() % 101;
		 pStudentData[i].iMat = rand() % 101;

		 pStudentData[i].Total = pStudentData[i].iKor +
			 pStudentData[i].iEng +
			 pStudentData[i].iMat;
		 pStudentData[i].Average = pStudentData[i].Total / 3.0f;
	 }
 }

 void DataPrint()//성적 출력
 {
	 if (pStudentData == 0)
	 {
		 return;
	 }system("cls");
	 printf("\n====================================================");
	 printf("\n=================성적 관리 프로그램=================");
	 printf("\n====================================================");
	 printf("\n번호\t이름\t국어\t영어\t수학\t총점\t평균");
	 printf("\n====================================================");

	 for (int i = 0; i < MaxCount; i++)
		 printf("\n %3d %8s %7d %7d %7d %7d %10.4f",
			 pStudentData[i].Index,
			 pStudentData[i].strName,
			 pStudentData[i].iKor,
			 pStudentData[i].iEng,
			 pStudentData[i].iMat,
			 pStudentData[i].Total,
			 pStudentData[i].Average);
 }
 
 void DataFindName()//이름검색
 {
	 char FindName[5] = { 0, };
	 printf("\n 이름을 입력하시오 : ");
	 scanf("%s", &FindName);

	 for (int i = 0; i < MaxCount; i++)
	 {
		 if (0 != strcmp(pStudentData[i].strName,FindName))
		 {
			 continue;
		 }
		 printf("\n%3d %8s %7d %7d %7d %7d %10.4f",
			 pStudentData[i].Index,
			 pStudentData[i].strName,
			 pStudentData[i].iKor,
			 pStudentData[i].iEng,
			 pStudentData[i].iMat,
			 pStudentData[i].Total,
			 pStudentData[i].Average);
		 break;
	 }
 }

 void DataFindIndex()//번호검색
 {
	 int FindIndex = -1;
	 system("cls");
		 printf("\n번호를 입력하시오 : ");
	 scanf("%d", &FindIndex);

	 if (FindIndex >= 0)
	 {
		 printf("\n%d %8s %7d %7d %7d %7d %10.4f",
			 pStudentData[FindIndex].Index,
			 pStudentData[FindIndex].strName,
			 pStudentData[FindIndex].iKor,
			 pStudentData[FindIndex].iEng,
			 pStudentData[FindIndex].iMat,
			 pStudentData[FindIndex].Total,
			 pStudentData[FindIndex].Average);
	 }
 }

 void DataSave()//데이터 저장
 {
	 FILE *fp;
	 fp = fopen("DATA.txt", "w");
		 fprintf(fp,"%d", MaxCount);
		 for (int i = 0; i < MaxCount; i++)
		 {
			 fprintf(fp, "\n%3d %8s %7d %7d %7d %7d %10.4f",
				 pStudentData[i].Index,
				 pStudentData[i].strName,
				 pStudentData[i].iKor,
				 pStudentData[i].iEng,
				 pStudentData[i].iMat,
				 pStudentData[i].Total,
				 pStudentData[i].Average);
		 }
		 fclose(fp);
 }

 void DataLoad()//데이터 로드
 {
	 FILE*fp;
	 fp = fopen("DATA.txt", "r");
	 if (fp == NULL)
	 {
		 return;
	 }
	 if (pStudentData != NULL)
	 {
		 free(pStudentData);
		 pStudentData = NULL;
	 }
	 fscanf(fp, "%d", &MaxCount);
	 if (pStudentData == NULL)
	 {
		 pStudentData = (Student*)malloc(sizeof(Student)*MaxCount);
	 }
	 for (int i = 0; i < MaxCount; i++)
	 {
		 fscanf(fp, "%d %s %d %d %d %d %f",
			 &pStudentData[i].Index,
			 pStudentData[i].strName,
			 &pStudentData[i].iKor,
			 &pStudentData[i].iEng,
			 &pStudentData[i].iMat,
			 &pStudentData[i].Total,
			 &pStudentData[i].Average);
	 }
	 fclose(fp);
	 DataPrint();
 }

 void DataAdd()
 {
	 
	 printf("신규 학생의 데이터를 입력 하시오:\n");
	 Student DataAdd;
	 printf("\n이름 : "); scanf("%s", DataAdd.strName);
	 printf("\n국어 : "); scanf("%d", &DataAdd.iKor);
	 printf("\n영어 : "); scanf("%d", &DataAdd.iEng);
	 printf("\n수학 : "); scanf("%d", &DataAdd.iMat);
	 DataAdd.Total = DataAdd.iKor + DataAdd.iEng + DataAdd.iMat;
	 DataAdd.Average = DataAdd.Total / 3.0f;
	 DataAdd.Index = MaxCount;
	 // 현재 메모리 데이터를 먼저 저장한다
	 ReNumbering();
	 DataSave();
	 //이후 신규 데이터를 파일의 끝에 추가 저장한다.
	 FILE *fp = fopen("DATA.txt", "r+");
	 if (fp == NULL)
	 {
		 if (fp == NULL)
		 {
			 return;
		 }
	 }
	 fprintf(fp, "%d", MaxCount + 1);
	 fseek(fp, 0, SEEK_END);
	 fprintf(fp, "\n%3d %8s %7d %7d %7d %7d %10.4f",
		 DataAdd.Index,
		 DataAdd.strName,
		 DataAdd.iKor,
		 DataAdd.iEng,
		 DataAdd.iMat,
		 DataAdd.Total,
		 DataAdd.Average);
	 fclose(fp);

	 DataLoad();
 }

 void DataDelete()
 {
	 int Delete=0;
	 printf("삭제시킬 정보:");
	 scanf("%d", &Delete);
	 for (int i = 0; i < MaxCount - Delete; i++) 
	 {
		 memmove(pStudentData + Delete+i, pStudentData + Delete + (1+i), sizeof(Student));
	 }
	 MaxCount = MaxCount - 1;

	 ReNumbering();
 }

 void ReNumbering()
{
	 for (int i = 0; i < MaxCount; i++)
	 {
		 pStudentData[i].Index = i;
	 }
}

 void DataEdit()
 {
	 int select = 0;
	 printf("수정할 학생의 번호를 선택해주세요");
	 scanf("%d", &select);

	 printf("이름: ");
	 scanf("%s", pStudentData[select].strName);
	 printf("국어: ");
	 scanf("%d", &pStudentData[select].iKor);
	 printf("영어: ");
	 scanf("%d", &pStudentData[select].iEng);
	 printf("수학: ");
	 scanf("%d", &pStudentData[select].iMat);

	 pStudentData[select].Total = pStudentData[select].iKor +
		 pStudentData[select].iEng + pStudentData[select].iMat;

	 pStudentData[select].Average = pStudentData[select].Total / 3.0f;

	 DataPrint();
 }

 void FindFile(void)
 {
	 struct _finddata_t c_file;
	 intptr_t hFile;

	 if ((hFile = _findfirst("*.txt", &c_file)) == -1L)
		 printf("No files in current directory!\n");

	 else
	 {
		 printf("Listing of files\n\n");
		 printf("\nNOR RDO HID SYS ARC SUBDIR FILE DATE %25c SIZE\n", ' ');
		 printf("--- --- --- --- --- --- ---- ---- %25c", ' ');
		 //Find the rest of the .c files
		 do
		 {
			 char buffer[30];
			 printf((c_file.attrib & _A_NORMAL) ? " Y " : " N ");//일반 파일
			 printf((c_file.attrib & _A_RDONLY) ? " Y " : " N ");//읽기 전용
			 printf((c_file.attrib & _A_SYSTEM) ? " Y " : " N ");//시스템파일
			 printf((c_file.attrib & _A_HIDDEN) ? " Y " : " N ");//숨김파일
			 printf((c_file.attrib & _A_ARCH) ? " Y " : " N ");//보관파일(파일을 변경 및 지울때 사용됨)
			 printf((c_file.attrib & _A_SUBDIR) ? " Y " : " N ");//하위디렉토리

			 ctime_s(buffer, _countof(buffer), &c_file.size);

			 printf("%-12s %.24s %9Id\n",
				 c_file.name, ctime(&(c_file.time_write)), c_file.size);

			 SortFile(&c_file);

		 } while (_findnext(hFile, &c_file) == 0);

		 _findclose(hFile);
	 }
 }

 void SortFile(_finddata_t* c_file)
 {
	 //최대 100개만 저장한다.
	 if (g_MaxSaveFile >= MAX_SAVE_FILE)
	 {
		 return;
	 }

	 _finddata_t file;
	 int iIndex = 0;
	 for (iIndex = 0; iIndex < g_MaxSaveFile; iIndex++)
	 {
		 memcpy(&file, &g_SaveFileArray[iIndex], sizeof(_finddata_t));
		 if (file.time_create < c_file->time_create)
		 {
			 break;
		 }
	 }
	 for (int iCnt = g_MaxSaveFile; iCnt > iIndex; iCnt--)
	 {
		 memcpy(&g_SaveFileArray[iCnt],
			 &g_SaveFileArray[iCnt - 1], sizeof(_finddata_t));
	 }
	 memcpy(&g_SaveFileArray[iIndex], c_file, sizeof(_finddata_t));
	 g_MaxSaveFile++;
 }