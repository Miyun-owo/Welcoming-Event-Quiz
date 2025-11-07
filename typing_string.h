#include<iostream>
#include<string>
#include <thread>
#include <chrono>
#include <stdlib.h>
using namespace std;

void Sleep(int s)
{
    return this_thread::sleep_for(chrono::seconds(s));
}

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

void __printProgressBar(int progress, int total) {
    int barWidth = 50;
    float percentage = static_cast<float>(progress) / total;
    int filledWidth = static_cast<int>(barWidth * percentage);

    cout << "\r[";
    for (int i = 0; i < filledWidth; ++i) {
        cout << "#";
    }
    for (int i = filledWidth; i < barWidth; ++i) {
        cout << " ";
    }
    cout << "] " << static_cast<int>(percentage * 100.0) << "%";
    cout << flush; // Ensure immediate output
}
void ProgressBar(int totalSteps = 100)
{
    for (int i = 0; i <= totalSteps; ++i) {
        __printProgressBar(i, totalSteps);
        this_thread::sleep_for(chrono::milliseconds(rand()%70)); // Simulate work
    }
}
void erase()
{
    #if defined(_WIN32) || defined(WIN32)
        system("cls");
    #else
        system("clear");
    #endif
}