#include <iostream>

using namespace std;

int fibonachi(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonachi(n-1) + fibonachi(n-2);
}

int main() 
{
    cout << fibonachi(5);
    while(true){}
}