//main.cpp
#include <iostream>
#include "GameEngine.h"

#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "Welkom bij het Adventure Eindproject (Console)\n";
    Adventure::GameEngine engine;
    engine.run();
    std::cout << "Einde spel. Tot ziens.\n";
    return 0;
}
