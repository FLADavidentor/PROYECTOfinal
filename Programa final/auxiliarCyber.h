#ifdef _WIN32
#include <windows.h>
void gotoxy(int x, int y)  
{
    COORD coord = { (SHORT)x, (SHORT) y };  
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);    
} 

#elif __linux__  
#include <ncurses.h>
void gotoxy(int x, int y)
{
    move(y, x);
}

#else  
void gotoxy(int x, int y)
{
    printf("\033[%d;%df", y, x); 
}
#endif