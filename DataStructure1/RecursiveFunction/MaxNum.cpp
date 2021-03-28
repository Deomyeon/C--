#include <iostream>
#include <vector>
 
using namespace std;
 
int MaxNum(vector<int> v, int bigger, int index)
{
    if (index == v.size())
    {
        return bigger;
    }
    else
    {
        return MaxNum(v, (bigger > v[index]) ? bigger : v[index], index + 1);
    }
}
 
int main()
{
    int a;
    cout << "입력할 숫자의 개수를 입력해주세요.\n";
    cin >> a;
    vector<int> v(a);
    for (int i = 0; i < a; i++)
    {
        cout << i + 1 << "번째 숫자를 입력해주세요.\n";
        cin >> v[i];
    }
    
    cout << MaxNum(v, 0, 0);
  
    return 0;
}