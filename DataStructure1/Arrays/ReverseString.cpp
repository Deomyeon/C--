#include <iostream>
using namespace std;
 
int main() {
 
	int a[10][10] = { 0 };
	int i, j;
 
	for (i = 0; i < 10; i++)
		a[i][0] = 1;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (j > 0 && i > 0)
				a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
			if (a[i][j] > 0)
				cout << a[i][j] << " ";
		}
		cout << endl;
	}
 
	return 0;
}