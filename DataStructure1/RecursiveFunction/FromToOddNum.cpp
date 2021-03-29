#include <iostream>
#include <vector>

using namespace std;

void FromToOddNum(vector<int>& odds, int n1, int n2)
{
    int a = 0;
    if (n1 % 2)
    {
        a = n1 + 2;
    }
    else
    {
        a = n1 + 1;
    }
    if (n2 <= a )
        return;
    odds.push_back(a);
    FromToOddNum(odds, a, n2);
    
}

int main()
{
    int a = 0;
    int b = 0;
    vector<int> odds;
    cin >> a;
    cin >> b;
    if (b > a)
        FromToOddNum(odds, a, b);
    else
        FromToOddNum(odds, b, a);
    for (int i = 0; i < odds.size(); i++)
    {
        cout << odds[i] << "\t";
    }
    return 0;
}