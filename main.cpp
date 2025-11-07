#include "typing_string.h"
using namespace std;

#define PASSWORD "317"

void enter_password()
{
    string s; 
    cout << "enter password:";
    while(cin >> s)
    {
        erase();
        cout << "verifying password...";
        ProgressBar();
        erase();
        if(s == PASSWORD)break;
        else
        {
            cout << "WRONG PASSWORD!!!" << flush;
            Sleep(1);
            erase();
            cout << "enter password:";
        } 
    }
}

int main()
{
    enter_password();
}