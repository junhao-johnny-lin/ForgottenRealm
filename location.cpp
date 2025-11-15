#include "location.h"

void initializeLocations(GameMap& map) {
    map.locations["Araluen"]    = {"Araluen", 50, 13};
    map.locations["Redmont"]    = {"Redmont", 45, 14};
    map.locations["Gorlan"]     = {"Gorlan", 55, 14};
    map.locations["Caraway"]    = {"Caraway", 50, 12};
    map.locations["Hackham"]    = {"Hackham", 60, 12};
    map.locations["Norgate"]    = {"Norgate", 40, 12};
    map.locations["Forest"]     = {"Forest", 40, 13};
    map.locations["Thomtree"]   = {"Thomtree", 45, 15};
    map.locations["Seacliff"]   = {"Seacliff", 55, 15};
    map.locations["Western_World"] = {"Western_World", 40, 16};
    map.locations["Mountains"]  = {"Mountains", 50, 16};
    map.locations["Uthal_Plain"]= {"Uthal_Plain", 60, 16};
    map.locations["The_Fens"]   = {"The_Fens", 70, 16};
    map.locations["Solitary"]   = {"Solitary Plain", 60, 17};
    map.locations["Three_Step_Pass"] = {"3 Step Pass", 75, 17};

    map.locations["Celtica"]    = {"Celtica", 10, 20};
    map.locations["Plateau"]    = {"Morgarath's Plateau", 70, 20};

    map.locations["Picta"]      = {"Picta", 10, 6};
    map.locations["Drowned_Forest"] = {"Drowned Forest", 10, 7};
    map.locations["Hibernia"]   = {"Hibernia", 10, 11};
}
