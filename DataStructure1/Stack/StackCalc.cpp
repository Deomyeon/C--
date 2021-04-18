#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

int calc(vector<string>& exp, int startI, int endI)
{
    stack<int, vector<int>> value;
    char giho = '+';
    int temp = 0;
    for (int i = startI; i < endI; i++)
    {
        string target = exp.at(i);
        if (target.size() == 1)
        {
            switch (target.at(0))
            {
            case '+':
                giho = '+';
                break;
            case '-':
                giho = '-';
                break;
            case '*':
                giho = '*';
                break;
            case '/':
                giho = '/';
                break;
            default:
                switch (giho)
                {
                case '+':
                    value.push(target.at(0) - '0');
                    break;
                case '-':
                    value.push(-1 * (target.at(0) - '0'));
                    break;
                case '*':
                    temp = value.top();
                    value.pop();
                    value.push(temp * (target.at(0) - '0'));
                    break;
                case '/':
                    temp = value.top();
                    value.pop();
                    value.push(temp / (target.at(0) - '0'));
                    break;
                }
                break;
            }
        }
        else
        {
            switch (giho)
            {
            case '+':
                value.push(atoi(target.c_str()));
                break;
            case '-':
                value.push(-1 * (atoi(target.c_str())));
                break;
            case '*':
                temp = value.top();
                value.pop();
                value.push(temp * (atoi(target.c_str())));
                break;
            case '/':
                temp = value.top();
                value.pop();
                value.push(temp / (atoi(target.c_str())));
                break;
            }
        }
    }
    temp = value.size();
    int sum = 0;
    for (int i = 0; i < temp; i++)
    {
        sum += value.top();
        value.pop();
    }
    return sum;
}

int StackCalc(vector<string>&& exp, int count)
{
    int result = 0;
    int startI = -1;
    int endI = -1;
    for (int nyan = 0; nyan < count + 1; nyan++)
    {
        startI = -1;
        endI = -1;
        int co = 0;
        for (int i = 0; i < exp.size(); i++)
        {
            if ('(' == exp.at(i).at(0))
            {
                startI = i + 1;
                co++;
                if (count == co)
                    break;
            }
        }
        for (int i = startI; i < exp.size(); i++)
        {
            if (')' == exp.at(i).at(0))
            {
                endI = i;
                break;
            }
        }
        if (!~startI)
        {
            result = calc(exp, 0, exp.size());
        }
        else
        {
            int temp = calc(exp, startI, endI);
            int length = -startI + endI + 1;
            exp[startI - 1] = to_string(temp);
            for (int i = endI + 1; i < exp.size(); i++)
            {
                exp[startI] = exp[i];
                startI++;
            }
            for (int i = 0; i < length; i++)
            {
                exp.pop_back();
            }
            result = temp;
        }

    }


    return result;
}

int check(vector<string>& exp) // 잘못된 수식일 시, true 반환
{
    int result = 0;
    stack<int> value;
    stack<char> parenthesis;

    for (int i = 0; i < exp.size(); i++)
    {
        string target = exp.at(i);
        if (target.size() == 1)
        {
            switch (target.at(0))
            {
            case '+':
            case '-':
            case '*':
            case '/':
                value.push(target.at(0));
                break;
            case '(':
            case ')':
                parenthesis.push(target.at(0));
                break; 
            default:
                if (target.at(0) >= '0' && target.at(0) <= '9')
                    value.push(target.at(0) - '0');
                else
                    result = -1;
                break;
            }
        }
        else
        {
            bool b = true;
            for (int j = 0; j < target.length(); j++)
                if (!(target.at(j) == '-' || (target.at(j) >= '0' && target.at(j) <= '9')))
                    b = false;
            if (b)
                value.push(atoi(target.c_str()));
            else
                result = -1;
        }
    }

    int temp = parenthesis.size();
    int count = 0;
    for (int i = 0; i < temp; i++)
    {
        switch (parenthesis.top())
        {
        case '(':
            count--;
            break;
        case ')':
            count++;
            (!~result) ? 0 : result++;
            break;
        }
        parenthesis.pop();
    }
    if (count)
        result = -1;

    temp = value.size();
    count = 0;
    for (int i = 0; i < temp; i++)
    {
        switch (value.top())
        {
        case '+':
        case '-':
        case '*':
        case '/':
            (!count) ? result = -1 : count = 0;
            break;
        default:
            (count) ? result = -1 : count = 1;
            break;
        }
        value.pop();
    }
    return result;
}

int main()
{
    string s = "";
    getline(cin, s);
    vector<string> vs;
    stringstream ss(s);
    while (getline(ss, s, ' '))
    {
        vs.push_back(s);
    }

    int count = check(vs);
    if (~count)
    {
        cout << StackCalc(move(vs), count);
    }
    else
    {
        cout << "잘못된 수식입니다." << endl;
    }

    return 0;
}