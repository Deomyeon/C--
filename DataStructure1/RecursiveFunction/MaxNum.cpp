#include <iostream>
#include <stdarg.h>
 
using namespace std;
 
 
int NumArgument(int count, va_list args)
{ 
    int n = va_arg(args, int);
    if (count == 1)
    {
        return n;
    }
    else
    {
        int c = NumArgument(count - 1, args);
        return (n > c) ? n : c;
    }
}
 
int MaxNum(int count, ...)
{
    va_list args;
    va_start(args, count);
    int result = NumArgument(count, args);
    va_end(args);
    return result;
}
 
int main()
{
    // **(n, int 1, int 2, int 3, int 4, ..., int n)** 와 같은 식으로 입력
    cout << MaxNum(6, 17, 32, 33, 45, 79, 1);
 
    return 0;
}