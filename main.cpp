//#include <iostream>
//#include "map_old.h"
//#include <string>
#include "game.h"

#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

int main() {
#ifdef _WIN32
    // Forceer UTF-8 output in Windows console
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Game g;
    g.runLoop();
    return 0;
}
