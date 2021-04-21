#include <iostream>

#include "list.hpp"

using namespace std;

int main()
{

	list<int> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.pop_back();
	l.pop_front();
	l.erase(1);
	l.insert(0, 7);
	for (int i = 0; i < l.size(); i++)
	{
		cout << l[i] << " ";
	}


	return 0;
}