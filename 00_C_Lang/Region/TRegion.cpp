#include "TRegion.h"

int TRegion::notation = TRegion::POINT_POINT;

TRegion::TRegion(void)
{
	SetRect(0, 0, 0, 0); //������ 0���� �ʱ�ȭ
}
TRegion::TRegion(int I, int t, int r,int b)
{
	SetRect(I, t, r, b); //������ �־��� ������ �ʱ�ȭ
}

void TRegion::SetRect(int I, int t, int r, int b)
{
	m_iLeft = I;          //�������� x��ǥ ����
	m_iTop = t;            //�������� y��ǥ ����
	m_iRight = r;         //������ x��ǥ ����
	m_iBottom = b;       //������ y��ǥ ����
}
int TRegion::GetWidth()const
{
	return m_iRight - m_iLeft;
}
const int TRegion::GetHeight() const
{
	return m_iBottom - m_iTop;
}
void TRegion::GetStartPoint(int &x, int &y)const
{
	x = m_iLeft; // �������� x��ǥ ���
	y = m_iTop; //�������� y��ǥ ���
}
void TRegion::GetEndPoint(int &x, int &y)const
{
	x = m_iRight; //������ x��ǥ ���
	y = m_iBottom; //������ y��ǥ ���
}
void TRegion::GetCenterPoint(int &x, int &y)const
{
	x = (m_iLeft + m_iRight) / 2; //�߽����� x��ǥ���
	y = (m_iTop + m_iBottom) / 2; //�߽����� y��ǥ ���
}
bool TRegion::IsPointInRegion(int x, int y)const
{
	return(x >= m_iLeft && x <= m_iRight && y >= m_iTop && y <= m_iBottom);
}
void TRegion::Move(int x, int y)
{
	m_iLeft += x;            //�������� x��ǥ �̵�
	m_iRight += x;           //������ x��ǥ �̵�
	m_iTop += y;             //�������� y��ǥ �̵�
	m_iBottom += y;          //������ y��ǥ �̵�
}
void TRegion::Resize(int width, int height)
{
	int x, y;
	GetCenterPoint(x, y);// �߽��� ��ǥ ���
	m_iLeft = x - width / 2; //�߽����κ��� ���α��� ���ݸ�ŭ �̵�
	m_iTop = y - height / 2; //�߽����κ��� ���α��� ���ݸ�ŭ �̵�
	m_iRight = m_iLeft + width; //���α��̰� width�� �ǵ��� ����
	m_iBottom = m_iTop + height; //���α��̰� height�� �ǵ��� ����
}
void TRegion::UnionRegion(const TRegion &r1, const TRegion &r2)
{
	m_iLeft = r1.m_iLeft < r2.m_iLeft ? r1.m_iLeft : r2.m_iLeft;
	m_iRight = r1.m_iRight > r2.m_iRight ? r1.m_iRight : r2.m_iRight;
	m_iTop = r1.m_iTop < r2.m_iTop ? r1.m_iTop : r2.m_iTop;
	m_iBottom = r1.m_iBottom > r2.m_iBottom ? r1.m_iBottom : r2.m_iBottom;
}
bool TRegion::IntersectRegion(const TRegion &r1, const TRegion &r2)
{
	m_iLeft = r1.m_iLeft > r2.m_iLeft ? r1.m_iLeft : r2.m_iLeft;
	m_iRight = r1.m_iRight < r2.m_iRight ? r1.m_iRight : r2.m_iRight;
	m_iTop = r1.m_iTop > r2.m_iTop ? r1.m_iTop : r2.m_iTop;
	m_iBottom = r1.m_iBottom < r2.m_iBottom ? r1.m_iBottom : r2.m_iBottom;
	// ���� �Ǵ� ������ ��ø�Ǿ��� �� ������ �������� �ʾҴ�. 
	// �������� �������� �ʴ� ���
	if (m_iLeft >= m_iRight || m_iTop >= m_iBottom)
	{
		m_iLeft = m_iTop = m_iRight = m_iBottom = 0;
		return false;
	}
	return true;
}
void TRegion::SetNotation(int n)
{
	notation = n;
}

void TRegion::Show(void)
{
	if (notation == POINT_POINT)	// ������/���� ����
	{
		printf("(%d, %d), (%d, %d)\n", m_iLeft, m_iTop, m_iRight, m_iBottom);
	}
	else					// ������/����, ����/���� ����
	{
		printf("(%d, %d), [%d x %d]\n", m_iLeft, m_iTop, GetWidth(), GetHeight());
	}
}
