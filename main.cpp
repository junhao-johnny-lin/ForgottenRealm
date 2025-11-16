#include <iostream>
#include "map.h"
#include <string>


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

    GameMap myMap;
    cout << "Dit is de wereldkaart van Araluen:\n\n";
    myMap.draw();

    cout << "\nWaar wil je starten?\n";
    string keuze;
     getline(cin >> ws, keuze); // ws = skip leading whitespace
    myMap.setHeroLocation(keuze);

    myMap.draw();

    return 0;
}
