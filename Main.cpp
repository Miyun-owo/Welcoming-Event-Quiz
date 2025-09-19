#include<iostream>
#include<string>
#include <windows.h>
using namespace std;

class typing_string : public string 
{
private:
    
public:
    int wait_time = 100;
    typing_string(const char s[])
    {
        assign(s);
        return;
    }
    typing_string(string s)
    {
        assign(s);
        return;
    }
};

ostream &operator<<(ostream &out, typing_string &s)
{
    for(auto &i : s)
    {
        cout << i;
        Sleep(s.wait_time);
    }
    return out;
}

int main()
{
    typing_string s = "Hello, world";
    s += "!!!";
    cout << s;
}