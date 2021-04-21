#include <iostream>

#include "queue.hpp"

using namespace std;

int main()
{

	queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	q.pop();
	q.pop();
	int temp = q.size();
	for (int i = 0; i < temp; i++)
	{
		cout << q.front() << " ";
		q.pop();
	}


	return 0;
}