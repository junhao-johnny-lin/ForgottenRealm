// map.cpp
#include "map.h"
#include "location.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

GameMap::GameMap() {
    initializeLocations(*this);   // locaties vullen via location.cpp
     heroLocationName = "";
}

void GameMap::setHeroLocation(const string& locNameRaw) {
    string locName = locNameRaw;
    locName.erase(remove_if(locName.begin(), locName.end(), ::isspace), locName.end());
    transform(locName.begin(), locName.end(), locName.begin(), ::tolower);

    if (locName == "3 Step Pass" || locName == "3steppass") {
        int keuze = 0;
        while (true) {
            cout << "\nJe bent aangekomen bij 3 Step Pass.\n";
            cout << "Kies via welke route je wilt betreden:\n";
            cout << "  1. Vanuit Araluen\n";
            cout << "  2. Vanuit Celtica\n";
            cout << "  3. Vanuit Morgarath's Plateau\n";
            cout << "Maak je keuze (1-3): ";

            if (cin >> keuze && keuze >= 1 && keuze <= 3) break;
            cout << "⚠️ Ongeldige invoer. Probeer opnieuw.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (keuze) {
        case 1: heroLocationName = "3 Step Pass (Araluen)"; break;
        case 2: heroLocationName = "3 Step Pass (Celtica)"; break;
        case 3: heroLocationName = "3 Step Pass (Plateau)"; break;
        }
        return;
    }

    for (const auto& [key, loc] : locations) {
        string keyNorm = key;
        keyNorm.erase(remove_if(keyNorm.begin(), keyNorm.end(), ::isspace), keyNorm.end());
        transform(keyNorm.begin(), keyNorm.end(), keyNorm.begin(), ::tolower);

        if (keyNorm == locName) {
            heroLocationName = loc.name;
            return;
        }
    }

    cout << "Onbekende locatie. Je start in Araluen.\n";
    heroLocationName = "Araluen";
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
        "│                    │         Solitary Plain   3 Step Pass          │                    │",
        "│                    └───────────────────────────────────────────────┘                    │",
        "│                                                                                         │",
        "│   ┌─────────────────┐                                        ┌─────────────────────┐    │",
        "│   │     CELTICA     │                                        │  MORGARATH'S        │    │",
        "│   │   (ZUIDWEST)    │                                        │    PLATEAU          │    │",
        "│   │   Villages      │                                        │  3 Step Pass        │    │",
        "│   │  3 Step Pass    │                                        │  Mountains          │    │",
        "│   └─────────────────┘                                        │  South Cliffs       │    │",
        "│                                                              └─────────────────────┘    │",
        "│                                                                                         │",
        "│                                       N                                                 │",
        "│                                       ↑                                                 │",
        "│                                 W ←   +   → E                                           │",
        "│                                       ↓                                                 │",
        "│                                       S                                                 │",
        "└─────────────────────────────────────────────────────────────────────────────────────────┘"
    };

    if (!heroLocationName.empty()) {
        for (auto& line : map) {
            size_t pos = line.find(heroLocationName);
            if (pos != string::npos) {
                size_t x = pos + heroLocationName.length();
                while (x < line.size() && line[x] != ' ') ++x;
                if (x < line.size()) {
                    line.insert(x, " X");
                }
                break;
            }
        }
    }

    for (const auto& line : map) {
        cout << line << '\n';
    }
    cout << "You have been summoned in the forgotten realm.\n";
    if (!heroLocationName.empty())
        cout << "Your journey begins in " << heroLocationName << ".\n";
    else
        cout << "Your journey begins...\n";
    cout << "The kingdom awaits your courage and wisdom!\n";
}
void GameMap::listAvailableLocations() const {
    cout << "Beschikbare locaties:\n";
    for (const auto& [key, loc] : locations) {
        cout << " - " << loc.name << '\n';
    }
}
