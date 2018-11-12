#include "Tpoint.h"

Tpoint Tpoint::operator++(void)//������
{
	++x, ++y;
	return *this;
}
Tpoint Tpoint::operator++(int) //������
{
	Tpoint temp = *this;
	++x, ++y;
	return temp;
}
Tpoint Tpoint::operator+(const Tpoint &pt)const
{
	return Tpoint(x + pt.x, y + pt.y);
}
Tpoint Tpoint::operator-(const Tpoint &pt)const
{
	return Tpoint(x - pt.x, y - pt.y);
}
Tpoint Tpoint::operator*(int mag)const
{
	return Tpoint(x*mag, y*mag);
}
Tpoint Tpoint::operator/(int div)const
{
	return Tpoint(x / div, y / div);
}
Tpoint operator*(int mag, const Tpoint &pt)
{
	return Tpoint(pt.x*mag, pt.y*mag);
}
Tpoint operator/(int div, const Tpoint &pt)
{
	return Tpoint(pt.x / div, pt.y / div);
}
Tpoint &Tpoint::operator=(const Tpoint &pt)
{
	x = pt.x; y = pt.y;
	return *this;
}
Tpoint &Tpoint::operator+=(const Tpoint &pt)
{
	x += pt.x; y += pt.y;
	return *this;
}
Tpoint &Tpoint::operator-=(const Tpoint &pt)
{
	x -= pt.x; y -= pt.y;
	return *this;
}
Tpoint &Tpoint::operator*=(const Tpoint &pt)
{
	x *= pt.x; y *= pt.y;
	return *this;
}
Tpoint &Tpoint::operator/=(const Tpoint &pt)
{
	x /= pt.x; y /= pt.y;
	return *this;
}
Tpoint &Tpoint::operator*=(int mag)
{
	x *= mag; y *= mag;
	return *this;
}
Tpoint &Tpoint::operator/=(int div)
{
	x /= div; y /= div;
	return *this;
}
bool Tpoint::operator==(const Tpoint &pt)const
{
	return(x == pt.x &&y == pt.y); //x,y�� ��� ������ ture
}
bool Tpoint::operator !=(const Tpoint &pt)const
{
	return (x != pt.x || y != pt.y); //x,y �� �ϳ��� �ٸ��� ture
}
int &Tpoint::operator[](int index)
{
	if (index == 0)
		return x;
	return y;
}
void *Tpoint::operator new(size_t size)
{
	return malloc(size);
}
void Tpoint::operator delete(void *p)
{
	free(p);
}
ostream &operator<<(ostream &os, const Tpoint &pt)
{
	os << "(" << pt.x << "," << pt.y << ")";
	return os;
}
istream &operator>>(istream &is, Tpoint &pt)
{
	is >> pt.x;
	is >> pt.y;
	return is;
}
Tpoint Tpoint::operator*(const Tpoint &c)
{
	Tpoint temp;
	temp.x = x * c.x;
	temp.y = y * c.y;
	return temp;
}

Tpoint Tpoint::operator/(const Tpoint &c)
{
	Tpoint temp;
	temp.x = x / c.x;
	temp.y = y / c.y;
	return temp;
}
void Tpoint::SetPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}
void Tpoint::Move(int _x, int _y)
{
	x += _x;
	y += _y;
}
void Tpoint::Show(void)
{
	cout << "(" << x << "," << y << ")" << endl;
}
Tpoint::Tpoint()
{
	cout << "Constuctor" << endl;
}
Tpoint::Tpoint(int x, int y)
{
	this->x = x;
	this->y = y;
	cout << "Constuctor" << endl;
}


Tpoint::~Tpoint()
{
	cout << "Distructor" << endl;
}
