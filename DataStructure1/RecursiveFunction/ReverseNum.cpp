#include <iostream>

using namespace std;

int ReverseNum(int n, int num)
{
    if (n < 10)
        return n;
    else
    {
        int a = 0;   
        a += (n % 10) * num;
        return a + ReverseNum(n / 10, num / 10);
    }
}

int main()
{

    cout << ReverseNum(3527445, 1000000) << endl;

    return 0;
}