// map.h
#pragma once
#include <string>
#include <unordered_map>

struct LocInfo {
    std::string label;
    int id = 0;
    int visited = 0;
    // voeg hier extra velden toe indien nodig, bv. hasDungeon, accessible, hasInn, etc.
    bool accessible = true;
    bool hasDungeon = false;
    bool hasInn = false;
};

struct WorldMap {
    // key = canonical key zoals "Villages", value = info
    std::unordered_map<std::string, LocInfo> locations;
};
