#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct Location {
    std::string label;
    bool visited = false;
    bool accessible = false;
    bool hasTrainer = false;
    bool hasCamp = false;
    bool hasDungeon = false;
    bool hasInn = false;
    bool dungeonCleared = false;
};

void renderMap(const std::unordered_map<std::string, Location>& nodes);
