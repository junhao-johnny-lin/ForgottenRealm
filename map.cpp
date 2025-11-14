#include "map.h"
#include <iostream>
#include "map.h"
#include <iostream>
using namespace std;

GameMap::GameMap() {}

void GameMap::draw() {

cout << "┌─────────────────────────────────────────────────────────────────────────────────────────┐\n"
     << "│                                     KAART VAN ARALUEN                                   │\n"
     << "├─────────────────────────────────────────────────────────────────────────────────────────┤\n"
     << "│                                                                                         │\n"
     << "│   ┌─────────────────┐                                                                   │\n"
     << "│   │     PICTA       │                                                                   │\n"
     << "│   │    (NOORDEN)    │                                                                   │\n"
     << "│   │  Drowned Forest │                                                                   │\n"
     << "│   └─────────────────┘                                                                   │\n"
     << "│                                                                                         │\n"
     << "│  ┌────────┐        ┌───────────────────────────────────────────────┐                    │\n"
     << "│  │        │        │                  ARALUEN                      │                    │\n"
     << "│  │HIBERNIA│        │                 (CENTRAAL)                    │                    │\n"
     << "│  │        │        │                                               │                    │\n"
     << "│  └────────┘        │  Norgate                    caraway           │                    │\n"
     << "│                    │  Forest        Araluen      Hackham           │                    │\n"
     << "│                    │  Redmont       Gorlan                         │                    │\n"
     << "│                    │                           Thomtree  seacliff  │                    │\n"
     << "│                    │ Western_World  Mountains Uthal_Plain The_Fens │                    │\n"
     << "│                    │         Solitary Plain                        │                    │\n"
     << "│                    │                                               │                    │\n"
     << "│                    └───────────────────────────────────────────────┘                    │\n"
     << "│                                                                                         │\n"
     << "│   ┌─────────────────┐                                        ┌─────────────────────┐    │\n"
     << "│   │     CELTICA     │                                        │  MORGARATH'S        │    │\n"
     << "│   │   (ZUIDWEST)    │                                        │    PLATEAU          │    │\n"
     << "│   └─────────────────┘                                        └─────────────────────┘    │\n"
     << "│                                                                                         │\n"
     << "│                                       N                                                 │\n"
     << "│                                       ↑                                                 │\n"
     << "│                                 W ←   +   → E                                           │\n"
     << "│                                       ↓                                                 │\n"
     << "│                                       S                                                 │\n"
     << "└─────────────────────────────────────────────────────────────────────────────────────────┘\n"
     << "You have been summoned in the forgotten realm.\n"
     << "This kingdom hasn't fallen yet.\n"
     << "Its future is in your hands to save this realm!!\n"
     << endl;
}
