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

     // Game-loop
     while (true) {
         // Toon kaart met huidige marker
         myMap.draw();

         // Toon huidige locatie
         if (!myMap.getHeroLocation().empty()) {
             cout << "Je huidige locatie is: " << myMap.getHeroLocation() << "\n";
         }

         // Vraag nieuwe bestemming
         cout << "\nTyp een nieuwe locatie, 'map' om de kaart opnieuw te zien, of 'stop' om te stoppen:\n";
         getline(cin >> ws, keuze);

         if (keuze == "stop") break;
         if (keuze == "map") {
             continue; // kaart wordt toch al getoond aan het begin van de loop
         }

         // Verplaats held
         myMap.setHeroLocation(keuze);
     }
    return 0;
}
