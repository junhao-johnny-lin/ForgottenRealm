#pragma once
#include <string>
#include <vector>

struct DungeonFloor {
    int floorIndex = 0;
    bool hasBoss = false;
    std::string label;
    int encounterCount = 1;
};

struct Dungeon {
    std::string id;
    std::string name;
    std::string entranceKey;
    int floorsCount = 0;
    std::vector<DungeonFloor> floors;
};

Dungeon makeDungeon(const std::string& id, const std::string& name, const std::string& entranceKey, int floors);
