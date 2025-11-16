#include "location.h"
//#include <iostream>

using namespace std;

void initializeLocations(GameMap& map) {
    // Picta sublocatie
    map.locations["Drowned_Forest"] = {"Drowned_Forest", 10, 0};

    // Hibernia
    map.locations["Hibernia"]       = {"HIBERNIA", 11, 0};

    // Araluen blok
    map.locations["Norgate"]        = {"Norgate", 12, 0};
    map.locations["Forest"]         = {"Forest", 13, 0};
    map.locations["Araluen"]        = {"Araluen", 14, 0};
    map.locations["3 Step Pass (Araluen)"] = {"3 Step Pass (Araluen)", 15, 0};
    map.locations["Hackham"]        = {"Hackham", 16, 0};
    map.locations["Redmont"]        = {"Redmont", 17, 0};
    map.locations["Gorlan"]         = {"Gorlan", 18, 0};
    map.locations["Caraway"]        = {"Caraway", 19, 0};
    map.locations["Thomtree"]       = {"Thomtree", 20, 0};
    map.locations["Seacliff"]       = {"Seacliff", 21, 0};
    map.locations["Western_World"]  = {"Western_World", 22, 0};
    map.locations["Mountains"]      = {"Mountains", 23, 0};
    map.locations["Uthal_Plain"]    = {"Uthal_Plain", 24, 0};
    map.locations["The_Fens"]       = {"The_Fens", 25, 0};
    map.locations["Solitary Plain"] = {"Solitary Plain", 26, 0};

    // Celtica sublocaties
    map.locations["Villages"]       = {"Villages", 27, 0};
    map.locations["3 Step Pass (Celtica)"] = {"3 Step Pass (Celtica)", 28, 0};

    // Morgarath's Plateau sublocaties
    map.locations["3 Step Pass (Plateau)"] = {"3 Step Pass (Plateau)", 29, 0};
    map.locations["Mountains (Plateau)"]   = {"Mountains (Plateau)", 30, 0};
    map.locations["South Cliffs"]          = {"South Cliffs", 31, 0};
}
