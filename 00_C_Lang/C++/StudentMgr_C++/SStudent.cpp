#include "SStudent.h"


void SStudent::Print()
{
	cout << "번호 : " << sData.iindex << endl;
	cout << "이름 : " << sData.strName << endl;
	cout << "국어 : " << sData.iKor << endl;
	cout << "영어 : " << sData.iEng << endl;
	cout << "수학 : " << sData.iMat << endl;
	cout << "총합 : " << sData.iTotal << endl;
	cout << "평균 : " << sData.Average << endl << endl;

	system("pause");
}
void SStudent::inputData(int Cnt)
{
	
		sData.strName[0] = 65 + rand() % 26;
		sData.strName[1] = 65 + rand() % 26;
		sData.strName[2] = 65 + rand() % 26;
		sData.strName[3] = '\0';

		sData.iindex = Cnt;
		sData.iKor = rand() % 101;
		sData.iEng = rand() % 101;
		sData.iMat = rand() % 101;

		sData.iTotal = sData.iKor + sData.iEng + sData.iMat;

		sData.Average = sData.iTotal / 3.0f;
	
}
void SStudent::SetData(char strName[],int iindex,int iKor,int iEng,int iMat,int iTotal,float Average)
{
	sData.iindex = iindex;
	sData.iKor = iKor;
	sData.iEng = iEng;
	sData.iMat = iMat;
	sData.iTotal = iTotal;
	sData.Average = Average;

	strcpy(sData.strName, strName);
}
StudentData SStudent::GetData()
{
	return sData;
}

SStudent::SStudent()
{
}


SStudent::~SStudent()
{
}
