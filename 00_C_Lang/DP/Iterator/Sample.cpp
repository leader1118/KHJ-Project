#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> V;

	V.push_back(10);
	V.push_back(20);
	V.push_back(30);
	V.push_back(40);
	V.push_back(50);

	vector<int>::iterator iter = V.begin();

	cout << iter[3] << endl;

	iter += 2;
	cout << *iter << endl;
	cout << endl;

	for (iter = V.begin(); iter != V.end(); ++iter)
	{
		cout << *iter << endl;
	}

	system("pause");
	return 0;

}
