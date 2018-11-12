#include "Node.h"
#include "SingleLinkedList.h"
#include <windows.h>

void main()
{
	SingleLinkedList List;
	SNode* pTestNode = new SNode(List.m_iCount);
	List.AddNode();
	List.AddNode();
	List.AddNode();
	List.AddNode();
	List.AddNode(pTestNode);
	List.ShowAllData();

	std::cout << std::endl;

	List.DelNode(1);
	List.ShowAllData();

	std::cout << std::endl;

	List.DelNode(3);
	List.ShowAllData();

	std::cout << std::endl;

	List.DelNode(4);
	List.ShowAllData();

}