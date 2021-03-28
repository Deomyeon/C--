#include <iostream>

using namespace std;

int SumNumDigit(int n)
{
    if (n < 10)
        return n;
    else
    {
        return n % 10 + SumNumDigit(n / 10);
    }
}

int main()
{
    int a;
    cin >> a;
    cout << SumNumDigit(a);

    return 0;
}