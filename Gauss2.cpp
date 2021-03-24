#include <iostream>

using namespace std;

int gauss(int n)
{
    if (n == 1)
        return 1;
    else
        return n + gauss(n - 1);
}

int main()
{
    cout << gauss(100);
    while(true){}
    return 0;
}