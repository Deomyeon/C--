#include <iostream>

using namespace std;

void Factorial(int64_t a[])
{
    a[0] = 1;
    for (int i = 1; i < 25; i++)
    {
        a[i] = i * a[i - 1];
    }
}

int main()
{
    int64_t a[30] = {0};
    Factorial(a);

    cout << a[6] << endl;
    cout << a[10] << endl;

    while(true)
    {}
    return 0;
}