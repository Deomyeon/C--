#include <iostream>

using namespace std;

int Gauss(int n)
{
    return ((1+n) * n) / 2;
}

int main()
{
    cout << Gauss(200);
    while(true){}

    return 0;
}