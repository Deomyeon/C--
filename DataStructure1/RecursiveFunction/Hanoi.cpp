#include <iostream>

using namespace std;

void Hanoi(int n, int start, int to, int end)
{
    if (n == 1)
        cout << start << "->" << end << endl;
    else
    {
        Hanoi(n - 1, start, end, to);
        cout << start << "->" << end << endl;
        Hanoi(n - 1, to, start, end);
    }
}

int main()
{
    Hanoi(3, 0, 1, 2);
    while (true)
    {
        /* code */
    }
    
    return 0;
}
