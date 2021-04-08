#include <iostream>
#include "./DataStructure/stack.hpp"

using namespace std;

int main()
{

    stack<char> chStack;
    chStack.push('A');
    chStack.push('B');
    chStack.push('C');
    cout << chStack.top();
    chStack.pop();
    cout << chStack.top();
    chStack.pop();
    chStack.push('D');
    cout << chStack.top();
    chStack.pop();
    cout << chStack.top();
    chStack.pop();
    
    return 0;
}