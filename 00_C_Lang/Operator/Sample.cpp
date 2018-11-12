//연산자 오버로딩
#include "Tpoint.h"
void(Tpoint:: *fp)();
void Execute(Tpoint* the)
{
	if (fp != NULL)
	{
		(the->*fp)();
	}
}
int main(void)
{
	Tpoint p1(0, 0), p2, p3, p4;
	p2 = ++p1;
	p1.Show();
	p2.Show();

	p1->Show();
	(*p1).Show();
	Tpoint* pData = new Tpoint();
	pData->Show();

	p3 = p1++;
	p1.Show();
	p3.Show();

	p4 = p1 + p2;
	p4.Show();

	Tpoint p5(10, 20), p6, p7, p8;
	p6 = p5 * 2;
	p6.Show();
	p6 = 2 * p5;
	p6.Show();

	p7 = p5 / 2;
	p7.Show();
	p8 = 2 / p5;
	p8.Show();

	p5 += p4;
	p5.Show();
	p6 -= p5;
	p6.Show();

	p5 *= 2;
	p5.Show();
	p6 /= 2;
	p6.Show();

	p5 *= p4;
	p5.Show();
	p6 /= p4;
	p6.Show();

	if (p5 == p6)cout << "같다.";
	if (p5 != p6)cout << "다르다.";

	cout << p6[0] << endl;
	cout << p6[1] << endl;

	Tpoint a, b, c;
	cout << "첫번째 입력: ";
	cin >> a;
	cout << "두번쨰 입력:";
	cin >> b;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "a+b = " << a + b << endl;
	cout << "a-b = " << a - b << endl;
	cout << "a*b = " << a * b << endl;
	cout << "a/b = " << a / b << endl;

	Tpoint* d = new Tpoint();
	d->SetPosition(10, 10);
	cout << *d;

	fp = &Tpoint::Show;
	Execute(d);

	d->m_fp = &Tpoint::Show;
	(*d) > &a;
	d->Execute();
	delete d;
	return 0;
}