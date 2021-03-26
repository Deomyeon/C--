#include <iostream>

using namespace std;


void TableTimes(int n, int i)
{
    if (i == 10)
        return;
    else
    {
        cout << n << " x " << i << " = " << n * i << endl;
        TableTimes(n, i + 1);
        return;
    }
}

void MultiplyTable(int n)
{
    if (n == 10)
        return;
    else
    {
        TableTimes(n, 1);
        MultiplyTable(n + 1);
        return;
    }
}

int main()
{

    MultiplyTable(2);

    return 0;
}