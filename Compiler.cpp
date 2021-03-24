#include <iostream>
#include <windows.h>
#include <direct.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream ifs;
    ofstream ofs;
    string str1, str2, str3;
    cin >> str2;
    str1 = "C:/Users/ROG/Desktop/C++/";
    str1.append(str2);
    str1.append(".cpp");
    ifs.open(str1.c_str());

    if (ifs.is_open())
    {   
        ifs.close();

        str1 = "C:/Users/ROG/Desktop/C++/";
        str1.append(str2);
        _mkdir(str1.c_str());

        str1 = "cd C:/Users/ROG/Desktop/C++/";
        str1.append(str2);
        system(str1.c_str());

        str1 = "g++ -c C:/Users/ROG/Desktop/C++/";
        str1.append(str2);
        str1.append(".cpp");
        system(str1.c_str());
        
        str1 = "g++ -o ";
        str1.append(str2);
        str1.append(" ");
        str1.append(str2);
        str1.append(".o");
        system(str1.c_str());

        str1 = "C:/Users/ROG/Desktop/C++/Compiler/";
        str1.append(str2);
        str1.append(".o");
        str3 = "C:/Users/ROG/Desktop/C++/";
        str3.append(str2);
        str3.append("/");
        str3.append(str2);
        str3.append(".o");
        CopyFileA(str1.c_str(), str3.c_str(), false);
        remove(str1.c_str());

        str1 = "C:/Users/ROG/Desktop/C++/Compiler/";
        str1.append(str2);
        str1.append(".exe");
        str3 = "C:/Users/ROG/Desktop/C++/";
        str3.append(str2);
        str3.append("/");
        str3.append(str2);
        str3.append(".exe");
        CopyFileA(str1.c_str(), str3.c_str(), false);
        remove(str1.c_str());

        str1 = "start %userprofile%/Desktop/C++/";
        str1.append(str2);
        system(str1.c_str());
    }

}