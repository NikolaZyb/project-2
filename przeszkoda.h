#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y);

class Przeszkoda
{
public:
    int lp;
    int x;
    int y;
    przeszkoda(int lp,int x, int y)
    {
    gotoxy(x,y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<"O";
    }
    void stworz();
};
