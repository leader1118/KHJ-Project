#include "SStudent.h"


void SStudent::Print()
{
	cout << "��ȣ : " << sData.iindex << endl;
	cout << "�̸� : " << sData.strName << endl;
	cout << "���� : " << sData.iKor << endl;
	cout << "���� : " << sData.iEng << endl;
	cout << "���� : " << sData.iMat << endl;
	cout << "���� : " << sData.iTotal << endl;
	cout << "��� : " << sData.Average << endl << endl;

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
