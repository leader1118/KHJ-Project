#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>

typedef struct StudentCode
{
	char strName[4];
	int Index;
	int iKor;
	int iEng;
	int iMat;
	int Total;
	float Average;
}Student;

Student *pStudentFile = 0;
int MAX=0;

enum WORK
{
	NewData,
	PrintData,
	FindName,
	FindIndex,
	AddData,
	DeleteData,
	SaveData,
	LoadData,
	EXIT = 99,
};

void DataNew();
void DataPrint();
void NameFind();
void IndexFind();
void DataAdd();
void DataDelete();
void DataSave();
void DataLoad();

void DataNew()
{
	printf("\n 학생의 수를 입력하시오 :");
	scanf("%d", &MAX);
	if (pStudentFile != NULL)
	{
		free(pStudentFile);
		pStudentFile = 0;
	}
	if (pStudentFile == NULL)
	{
		pStudentFile = (Student *)malloc(sizeof(Student)*MAX);
	}
	for (int i = 0; i < MAX; i++)
	{
		pStudentFile[i].strName[0] = 65 + rand() % 26;
		pStudentFile[i].strName[1] = 65 + rand() % 26;
		pStudentFile[i].strName[2] = 65 + rand() % 26;
		pStudentFile[i].strName[3] = '\0';

		pStudentFile[i].Index = i;
		pStudentFile[i].iKor = rand() % 101;
		pStudentFile[i].iEng = rand() % 101;
		pStudentFile[i].iMat = rand() % 101;

		pStudentFile[i].Total = pStudentFile[i].iKor + pStudentFile[i].iEng + pStudentFile[i].iMat;
		pStudentFile[i].Average = pStudentFile[i].Total / 3.0f;
	}
}