#pragma once
#include<iostream>
//const char*p=0; // 비상수 포인터 , 상수 데이터
//char* const p =0; //상수 포인터, 비상수 데이터
//const char* const p=0; //상수 포인터, 상수 데이터
//void a() const {} // 함수에서 멤버 변수 값 변경 불가능
//const 함수에서는 const 함수만 호출가능.

class TRegion
{
public:
	enum{POINT_POINT, POINT_SIZE};//시작점과  끝점, 시작점과 길이
	int m_iWidth;
	int m_iHeight;
private:
	//사각형 영역을 저장하기 위한 멤버변수들
	int m_iLeft; //시작점의 x좌표
	int m_iTop;  //시작점의 y좌표
	int m_iRight; //끝점의 x좌표
	int m_iBottom; //끝점의 y좌표
	//출력방식을 지정하기 위한 멤버변수
	static int notation; //POINT_POINT또는 POINT_SIZE
public:
	const TRegion* Get() const { return this; }
	const Tregion& GetRef() const { return *this; }//this ==자기를 칭하는 함수
	//사각형 영역에 대한 정보를 얻는 함수들
	const int GetLeft() { return m_iLeft; }
	const int GetTop() { return m_iTop; }
	const int* GetRight() { return &m_iRight; }
	const int& GetBottom() { return m_iBottom; }
	
	int GetWidth() const;                       //가로길이 얻기
	const int GetHeight() const;                //세로길이 얻기    
	void GetStartPoint(int &x, int &y)const;    //시작점 얻기    
	void GetEndPoint(int &x, int &y)const;      //끝점 얻기    
	void GetCenterPoint(int &x, int &y)const;   //중심점 얻기    
	bool IsPointInRegion(int x, int y)const;    //점이 영역 안에 있는지    
	// 사각형 영역을 설정하고 처리하는 함수들
	void SetRect(int I, int t, int r, int b, ); //영역 설정
	void Move(int x, int y);                     //위치 이동
	void Resize(int width, int height);          //크기 변경
	void UnionRegion(const TRegion &r1, const TRegion &r2); // 합집합
	bool IntersectRegion(const TRegion &r1, const TRegion &r2); // 교집합
	
	// 사각형 영역을 표시하기 위한 함수들
	void Show(void);                       //영역 출력
	static void SetNotation(int notation); //출력 방식

public:
	TRegion(void);          //생성자
	TRegion(int I, int t, int r, int b); //생성자
	
};

