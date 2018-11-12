#pragma once
#include<iostream>
//const char*p=0; // ���� ������ , ��� ������
//char* const p =0; //��� ������, ���� ������
//const char* const p=0; //��� ������, ��� ������
//void a() const {} // �Լ����� ��� ���� �� ���� �Ұ���
//const �Լ������� const �Լ��� ȣ�Ⱑ��.

class TRegion
{
public:
	enum{POINT_POINT, POINT_SIZE};//��������  ����, �������� ����
	int m_iWidth;
	int m_iHeight;
private:
	//�簢�� ������ �����ϱ� ���� ���������
	int m_iLeft; //�������� x��ǥ
	int m_iTop;  //�������� y��ǥ
	int m_iRight; //������ x��ǥ
	int m_iBottom; //������ y��ǥ
	//��¹���� �����ϱ� ���� �������
	static int notation; //POINT_POINT�Ǵ� POINT_SIZE
public:
	const TRegion* Get() const { return this; }
	const Tregion& GetRef() const { return *this; }//this ==�ڱ⸦ Ī�ϴ� �Լ�
	//�簢�� ������ ���� ������ ��� �Լ���
	const int GetLeft() { return m_iLeft; }
	const int GetTop() { return m_iTop; }
	const int* GetRight() { return &m_iRight; }
	const int& GetBottom() { return m_iBottom; }
	
	int GetWidth() const;                       //���α��� ���
	const int GetHeight() const;                //���α��� ���    
	void GetStartPoint(int &x, int &y)const;    //������ ���    
	void GetEndPoint(int &x, int &y)const;      //���� ���    
	void GetCenterPoint(int &x, int &y)const;   //�߽��� ���    
	bool IsPointInRegion(int x, int y)const;    //���� ���� �ȿ� �ִ���    
	// �簢�� ������ �����ϰ� ó���ϴ� �Լ���
	void SetRect(int I, int t, int r, int b, ); //���� ����
	void Move(int x, int y);                     //��ġ �̵�
	void Resize(int width, int height);          //ũ�� ����
	void UnionRegion(const TRegion &r1, const TRegion &r2); // ������
	bool IntersectRegion(const TRegion &r1, const TRegion &r2); // ������
	
	// �簢�� ������ ǥ���ϱ� ���� �Լ���
	void Show(void);                       //���� ���
	static void SetNotation(int notation); //��� ���

public:
	TRegion(void);          //������
	TRegion(int I, int t, int r, int b); //������
	
};

