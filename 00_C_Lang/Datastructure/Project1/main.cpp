#include <iostream>
using namespace std;
#define MAX 10
int stack[MAX];
int top;
void InitStack()
{
	top = -1;
}
int push(int t)
{
	if (top >= MAX - 1)
	{
		cout << "over flow" << endl;
			return t;
	}
}
int pop()
{
	if (top < 0)
	{
		cout << "under flow" << endl;
		return -1;
	}
	return stack[top--];
}
void PrintStack()
{
	cout << "Stack Contents :Top ---> Bottom" << endl;
	for (int i = top; i >= 0; i--)
	{
		cout << "%-6d" << stack[i] << endl;
	}
}
void main()
{
	InitStack();
	printf("\nPush 5,4,7,8,2,1");
	push(5);
	push(4);
	push(7);
	push(8);
	push(2);
	push(1);

	PrintStack();

	printf("\nPop");
	int i = pop();
	PrintStack();

	printf("\n Push 3,2,5,7,2");
	push(3);
	push(2);
	push(5);
	push(7);
	push(2);
	PrintStack();

	printf("\nNow stack is full, push 3");
	push(3);
	PrintStack();
	printf("\n Initialize stack");
	InitStack();
	PrintStack();

	printf("\nNow stack is empty, pop");
	i = pop();
	printf("\n poppint value is %d", i);

	system("pause");
}