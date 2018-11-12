#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
//∆˜¿Œ≈Õ

//void main()
//{
//	int var = 1;
//	int *ptr;
//	ptr = &var;
//
//	printf("Direct,var=%d\n", var);
//	printf("Indirect,var=%d\n", *ptr);
//	printf("The address of var=%d", &var);
//	printf("The address of var=%d", ptr);
//}

//void main()
//{
//	int Var1;
//	int Var2;
//	int *pVar = &Var1;
//
//	*pVar = 10;
//	printf("%d\n", Var1);
//
//	Var2 = *pVar;
//	printf("%d\n", Var2);
//
//	pVar = &Var2;
//	*pVar = 5;
//	printf("%d\n", Var2);
//}

//void main()
//{
//	int p=3;
//	int q=2;
//
//	printf("\n*p==%d, *q==%d\n", p,q);
//	printf("\n*p==%p, *q==%p\n", p,q);
//	printf("\n*p==%p, *q==%p\n", &p, &q);
//}

//void main()
//{
//	int *p;
//	int *q;
//	int a = 1;
//	int b = 2;
//	p = &a;
//	q = &b;
//
//	printf("\n&a==%p, a==%d, &b==%p, b==%d", &a, a, &b, b);
//	printf("\np==%p,*p==%d,q==%p,*q==%d\n",p,*p,q,*q);
//	
//}


void main()
{
	int a = 1;
	int b = 3;
	int *p;
	int *q;

	p = &a; q = &b;
		printf("\n*p=%d,*q=%d\n", *p, *q);

	call_ref(p, q);
	printf("\n *p=%d,*q=%d", *p, *q);

}
call_ref(int *x, int *y)
{
	*x = 3;
	*y = 5;
}