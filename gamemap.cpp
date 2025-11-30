// FILE: gamemap.cpp
#include "gamemap.h"
#include <iostream>


namespace Adventure {

GameMap::GameMap() {
    build();
}

void GameMap::build() {
    locations_.clear();

    // --- 18 REGIO’S ---
    locations_.emplace_back("Picta", "Noorden - Drowned Forest", true, true);
    locations_.emplace_back("Hibernia", "Eindgebied - Laatste dungeon + Ultimate Boss", true, true);
    locations_.emplace_back("Araluen", "Centraal Araluen", true, true);
    locations_.emplace_back("Norgate", "Stad uit Araluen", true, true);
    locations_.emplace_back("Redmont", "Stad uit Araluen", true, true);
    locations_.emplace_back("Gorlan", "Stad uit Araluen", true, true);
    locations_.emplace_back("Caraway", "Stad uit Araluen", true, true);
    locations_.emplace_back("Hackham", "Stad uit Araluen", true, true);
    locations_.emplace_back("Forest_Araluen", "Bossen van Araluen", true, true);
    locations_.emplace_back("Western_World", "Westelijke zone", true, true);
    locations_.emplace_back("Solitary_Plain", "Open vlakte", true, true);
    locations_.emplace_back("Three_Step_Pass_Araluen", "3 step pass (Araluen)", true, true);
    locations_.emplace_back("The_Fens", "Moerassen", true, true);
    locations_.emplace_back("Celtica", "Zuid-West - villages", true, true);
    locations_.emplace_back("Three_Step_Pass_Celtica", "3 step pass (Celtica)", true, true);
    locations_.emplace_back("Morgarath_Plateau", "Plateau van Morgarath", true, true);
    locations_.emplace_back("South_Cliffs", "Zuidelijke Kliffen", true, true);
    locations_.emplace_back("Mountains_Plateau", "Bergen van het Plateau", true, true);
}


void GameMap::draw() const {

    std::vector<std::string> map = {
        "┌─────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                     KAART VAN ARALUEN                                   │",
        "├─────────────────────────────────────────────────────────────────────────────────────────┤",
        "│                                                                                         │",
        "│   ┌─────────────────┐                                                                   │",
        "│   │     PICTA       │                                                                   │",
        "│   │    (NOORDEN)    │                                                                   │",
        "│   │ Drowned_Forest  │                                                                   │",
        "│   └─────────────────┘                                                                   │",
        "│                                                                                         │",
        "│  ┌─────────┐        ┌────────────────────────────────────────────────────┐              │",
        "│  │         │        │                  ARALUEN                           │              │",
        "│  │HIBERNIA │        │                 (CENTRAAL)                         │              │",
        "│  │         │        │  Norgate                    Caraway                │              │",
        "│  └─────────┘        │Forest(Araluen)  Araluen     Hackham                │              │",
        "│                     │  Redmont       Gorlan                              │              │",
        "│                     │                           Thomtree  Seacliff       │              │",
        "│                     │Western_World   Mountains   Uthal_Plain   The_Fens  │              │",
        "│                     │         Solitary Plain   3 Step Pass (Araluen)     │              │",
        "│                     └────────────────────────────────────────────────────┘              │",
        "│                                                                                         │",
        "│   ┌──────────────────────┐                              ┌──────────────────────┐        │",
        "│   │     CELTICA          │                              │  MORGARATH'S         │        │",
        "│   │   (ZUIDWEST)         │                              │    PLATEAU           │        │",
        "│   │   Villages           │                              │3 Step Pass (Plateau) │        │",
        "│   │3 Step Pass (Celtica) │                              │ Mountains (Plateau)  │        │",
        "│   └──────────────────────┘                              │  South Cliffs        │        │",
        "│                                                         └──────────────────────┘        │",
        "│                                                                                         │",
        "│                                       N                                                 │",
        "│                                       ↑                                                 │",
        "│                                 W ←   +   → E                                           │",
        "│                                       ↓                                                 │",
        "│                                       S                                                 │",
        "└─────────────────────────────────────────────────────────────────────────────────────────┘"
    };

    for (const std::string& line : map)
        std::cout << line << "\n";
}

const std::vector<Location>& GameMap::locations() const {
    return locations_;
}

Location* GameMap::getLocation(const std::string& id) {
    for (auto& loc : locations_)
        if (loc.id() == id)
            return &loc;
    return nullptr;
}

} // namespace Adventure
