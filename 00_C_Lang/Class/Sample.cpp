#include"TPoint.h"

int main(void)
{
	TPoint p1, p2; //Á¡ÀÇ ÁÂÇ¥¸¦ ÀúÀåÇÒ º¯¼ö ¼±¾ð

	p1.SetPosition(10, 20); //p1ÀÇ ÁÂÇ¥ ¼³Á¤
	p2.SetPosition(50, 60); //p2ÀÇ ÁÂÇ¥¼³Á¤

	p1.Move(5, 0); //p1ÀÇ ÁÂÇ¥ ÀÌµ¿
	p2.Move(0, 5); //p2ÀÇ ÁÂÇ¥ ÀÌµ¿

	p1.Show(); //p1ÀÇ ÁÂÇ¥¸¦ Ãâ·Â
	p2.Show(); //p2ÀÇ ÁÂÇ¥¸¦ Ãâ·Â

	_getch();
	return 0;
}