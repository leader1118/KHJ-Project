#include "TQueue.h"
#include <queue>
#include <deque>
void main()
{
	std::deque<int> queueList;
	queueList.push_back(0);
	queueList.push_back(1);
	queueList.push_back(2);
	int iA =queueList.front();
	int iB = queueList.back();
	queueList.pop_front();
	queueList.push_back();

    
	TQueue queue;
	queue.put(0);
	queue.put(1);
	queue.put(2);
	queue.put(3);
	queue.put(4);
	        queue.put(5);
	queue.Get();
	queue.put(6); // 0
	queue.put(7);
	queue.Get();
	queue.Get();
	queue.Get();
	queue.put(8);
	queue.put(9);
	queue.Get();
	queue.Get();

	queue.put(10);

}