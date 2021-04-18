#include <iostream>
#include <vector>
#include <stack>

using namespace std;

string ThousandPoint(int num)
{
    string result;
    stack<char, vector<char>> s;

    for (;num >= 1;)
    {
        s.push((num % 10) + '0');
        num /= 10;
        if (s.size() % 4 == 3)
            s.push(',');
    }
    int temp = s.size();
    for (int i = 0; i < temp; i++)
    {
        result.push_back(s.top());
        s.pop();
    }
    return result;
}

int main()
{

    int num;
    cin >> num;
    cout << ThousandPoint(num);

    return 0;
}