// FILE: src/GameMap.cpp
#include "GameMap.h"
#include "trainer_1_2.h"
#include "location_1_2.h"

#include <iostream>

namespace Adventure {

GameMap::GameMap() { build(); }
const std::vector<Location>& GameMap::locations() const { return locations_; }

void GameMap::build() {
    locations_.clear();

    // Hibernia index 0 - final zone
    Location h("Hibernia", "Final forest - Hibernia (endboss)");
    h.setDungeon(true);
    h.setInn(true);
    Trainer trh("Hibernia Elder");
    trh.addSkill({"hib_free","Winter's Grace","Start skill (free)",1,0,5});
    trh.addSkill({"hib_frost","Frost Nova","Area frost",10,2,20});
    h.setTrainer(trh);
    h.addAchievementId("hibernia_clear");
    locations_.push_back(h);

    // Araluen
    Location ar("Araluen", "Central Araluen");
    ar.setDungeon(true);
    Trainer tra("Araluen Trainer");
    tra.addSkill({"ar_slash","Slash","A basic slash",1,0,3});
    ar.setTrainer(tra);
    ar.addAchievementId("araluen_clear");
    locations_.push_back(ar);

    // Celtica
    Location cel("Celtica", "Celtica villages");
    cel.setDungeon(true);
    Trainer trc("Celtica Ranger");
    trc.addSkill({"cel_shot","Arrow Shot","Ranged attack",1,0,3});
    cel.setTrainer(trc);
    cel.addAchievementId("celtica_clear");
    locations_.push_back(cel);

    // Add other named locations until we have 18 total
    std::vector<std::pair<std::string,std::string>> extra = {
        {"Picto","Northern Drowned Forest"},
        {"Norgate","Norgate Village"},
        {"Caraway","Caraway Hamlet"},
        {"Redmont","Redmont Castle"},
        {"Gorlan","Gorlan"},
        {"Thomtree","Thomtree"},
        {"Seacliff","Seacliff"},
        {"Western_World","Western World"},
        {"Mountains","Mountain Range"},
        {"Uthal_Plain","Uthal Plain"},
        {"The_Fens","The Fens"},
        {"Solitary_Plain","Solitary Plain"},
        {"ThreeStep_Araluen","3 Step Pass (Araluen)"},
        {"Morgarath_Plateau","Morgarath's Plateau"},
        {"South_Cliffs","South Cliffs"}
    };

    for (size_t i = 0; i < extra.size() && locations_.size() < 18; ++i) {
        Location loc(extra[i].first, extra[i].second);
        loc.setDungeon(true); // everything except maybe some could have dungeons per your spec
        Trainer t(extra[i].first + " Trainer");
        t.addSkill({extra[i].first + "_basic", "Basic Strike", "Local basic strike", 1, 0, 3});
        loc.setTrainer(t);
        loc.addAchievementId(extra[i].first + "_clear");
        locations_.push_back(loc);
    }

    // ensure count 18
    while (locations_.size() < 18) {
        int n = (int)locations_.size() + 1;
        Location loc("Location" + std::to_string(n), "Wilderness " + std::to_string(n));
        loc.setDungeon(true);
        locations_.push_back(loc);
    }
}

const Location* GameMap::getLocationById(const std::string& id) const {
    for (const auto& l : locations_) if (l.id() == id) return &l;
    return nullptr;
}
Location* GameMap::getLocationById(const std::string& id) {
    for (auto& l : locations_) if (l.id() == id) return &l;
    return nullptr;
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
    for (const auto& l : map) std::cout << l << "\n";
}

} // namespace Adventure
