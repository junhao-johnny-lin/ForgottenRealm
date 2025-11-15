// map.cpp
#include "map.h"
#include "location.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

GameMap::GameMap() {
    initializeLocations(*this);   // locaties vullen via location.cpp
    heroX = -1;
    heroY = -1;
}

void GameMap::setHeroLocation(const std::string& locNameRaw) {
    std::string locName = locNameRaw;
    // normaliseer invoer
    locName.erase(remove_if(locName.begin(), locName.end(), ::isspace), locName.end());
    transform(locName.begin(), locName.end(), locName.begin(), ::tolower);

    for (const auto& [key, loc] : locations) {
        std::string keyNorm = key;
        keyNorm.erase(remove_if(keyNorm.begin(), keyNorm.end(), ::isspace), keyNorm.end());
        transform(keyNorm.begin(), keyNorm.end(), keyNorm.begin(), ::tolower);

        if (keyNorm == locName) {
            heroLocationName = loc.name;   // sla naam op
            heroX = loc.x;
            heroY = loc.y;
            return;
        }
    }

    std::cout << "Onbekende locatie. Je start in Araluen.\n";
    heroLocationName = "Araluen";
    heroX = locations["Araluen"].x;
    heroY = locations["Araluen"].y;
}
void GameMap::draw() const {
    vector<string> map = {
        "┌─────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                     KAART VAN ARALUEN                                   │",
        "├─────────────────────────────────────────────────────────────────────────────────────────┤",
        "│                                                                                         │",
        "│   ┌─────────────────┐                                                                   │",
        "│   │     PICTA       │                                                                   │",
        "│   │    (NOORDEN)    │                                                                   │",
        "│   │  Drowned Forest │                                                                   │",
        "│   └─────────────────┘                                                                   │",
        "│                                                                                         │",
        "│  ┌────────┐        ┌───────────────────────────────────────────────┐                    │",
        "│  │        │        │                  ARALUEN                      │                    │",
        "│  │HIBERNIA│        │                 (CENTRAAL)                    │                    │",
        "│  │        │        │  Norgate                    Caraway           │                    │",
        "│  └────────┘        │  Forest        Araluen      Hackham           │                    │",
        "│                    │  Redmont       Gorlan                         │                    │",
        "│                    │                           Thomtree  Seacliff  │                    │",
        "│                    │ Western_World  Mountains Uthal_Plain The_Fens │                    │",
        "│                    │         Solitary Plain                        │                    │",
        "│                    └───────────────────────────────────────────────┘                    │",
        "│                                                                                         │",
        "│   ┌─────────────────┐                                        ┌─────────────────────┐    │",
        "│   │     CELTICA     │                                        │  MORGARATH'S        │    │",
        "│   │   (ZUIDWEST)    │                                        │    PLATEAU          │    │",
        "│   └─────────────────┘                                        └─────────────────────┘    │",
        "│                                                                                         │",
        "│                                       N                                                 │",
        "│                                       ↑                                                 │",
        "│                                 W ←   +   → E                                           │",
        "│                                       ↓                                                 │",
        "│                                       S                                                 │",
        "└─────────────────────────────────────────────────────────────────────────────────────────┘"
    };

    if (!heroLocationName.empty()) {
        for (int y = 0; y < (int)map.size(); ++y) {
            size_t pos = map[y].find(heroLocationName);
            if (pos != std::string::npos) {
                size_t x = pos + heroLocationName.length();
                // zoek eerste spatie erachter
                while (x < map[y].size() && map[y][x] != ' ') ++x;
                if (x < map[y].size()) {
                    map[y][x] = 'X';
                }
                break;
            }
        }
    }

    for (const auto& line : map) {
        std::cout << line << '\n';
    }

    std::cout << "You have been summoned in the forgotten realm.\n";
    if (!heroLocationName.empty())
        std::cout << "Your journey begins in " << heroLocationName << ".\n";
    else
        std::cout << "Your journey begins...\n";
    std::cout << "The kingdom awaits your courage and wisdom!\n";
}
void GameMap::listAvailableLocations() const {
    cout << "Beschikbare locaties:\n";
    for (const auto& [key, loc] : locations) {
        cout << " - " << loc.name << '\n';
    }
}
