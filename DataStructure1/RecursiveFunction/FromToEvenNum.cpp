#include <iostream>
#include <vector>

using namespace std;

void FromToEvenNum(vector<int>& evens, int n1, int n2)
{
    int a = 0;
    if (n1 % 2)
    {
        a = n1 + 1;
    }
    else
    {
        a = n1 + 2;
    }
    if (n2 <= a )
        return;
    evens.push_back(a);
    FromToEvenNum(evens, a, n2);
    
}

int main()
{
    int a = 0;
    int b = 0;
    vector<int> evens;
    cin >> a;
    cin >> b;
    if (b > a)
        FromToEvenNum(evens, a, b);
    else
        FromToEvenNum(evens, b, a);
    for (int i = 0; i < evens.size(); i++)
    {
        cout << evens[i] << "\t";
    }
    return 0;
}