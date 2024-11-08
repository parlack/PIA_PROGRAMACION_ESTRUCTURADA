#include <windows.h>

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);

    /*
    RED = 4
    GREEN = 2
    BLUE = 1
    WHITE = 7   DEFAULT
    */
}
