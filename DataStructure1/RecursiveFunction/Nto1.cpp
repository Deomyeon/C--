#include <iostream>

using namespace std;

void Nto1(int n)
{
    if (n == 0)
        return;
    cout << n << " ";
    Nto1(n - 1);
}

int main()
{

    int n;
    cin >> n;

    Nto1(n);

    return 0;
}