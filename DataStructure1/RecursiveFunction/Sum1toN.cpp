#include <iostream>

using namespace std;

int Sum1toN(int n)
{
    if (n == 1)
        return 1;
    else
    {
        return n + Sum1toN(n - 1);
    }
}

int main()
{
    int n = 0; // int Min
    cin >> n;

    cout << Sum1toN(n) << endl;
    while(true){}
    return 0;
}