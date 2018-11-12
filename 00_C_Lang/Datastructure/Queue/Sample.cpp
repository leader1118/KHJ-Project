#include <iostream>
#define MAX 10
using namespace std;
int queue[MAX];
int front, rear;

void InitQueue()
{
	front = rear = 0;
}
void ClearQueue()
{
	front = rear;
}
int put(int t)
{
	if ((rear + 1) % MAX == front)
	{
		cout << "over flow" << endl;
		return -1;
	}
	queue[rear] = t;
	rear = ++rear % MAX;
	return t;
	
}
int get()
{
	if (front == rear)
	{
		cout << " under flow" << endl;
		return -1;
	}
	int i = queue[front];
	front = ++front % MAX;
	return i;
}
void PrintQueue()
{
	cout << " Queue Contents : Top ---> Bottom" << endl;
	for (int i = front; i != rear; i = ++i%MAX)
	{
		cout << "%-6d" << queue[i] << endl;
	}
}
void main()
{

	InitQueue();
	printf("\nPush 5,4,7,8,2,1");
	put(5);
	put(4);
	put(7);
	put(8);
	put(2);
	put(1);

	PrintQueue();

	printf("\nGet");
	int i = get();
	PrintQueue();

	printf("\n Put 3,2,5,7");
	put(3);
	put(2);
	put(5);
	put(7);
	PrintQueue();

	printf("\nNow queue is full, push 3");
	put(3);
	PrintQueue();

	printf("\n Initialize queue");
	ClearQueue();
	PrintQueue();

	printf("\nNow queue is empty, pop");
	i = get();
	printf("\n poppint value is %d", i);

	system("pause");
}