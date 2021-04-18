#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    stack<string, vector<string>> s;

    int size;
    cin >> size;

    for (int i = 0; i < size; i++)
    {
        string temp;
        cin >> temp;
        s.push(temp);
    }
    for (int i = 0; i < size; i++)
    {
        cout << s.top() << " ";
        s.pop();
    }

    return 0;
}