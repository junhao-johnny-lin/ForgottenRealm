// dungeon.h
#pragma once
#include <string>
#include <vector>

struct DungeonFloor {
    int floorIndex = 0;
    std::string label;
    std::vector<std::string> enemyIds;
};

struct Dungeon {
    std::string entranceKey;
    std::string id;
    std::string name;
    std::vector<DungeonFloor> floors;
};

std::vector<Dungeon> getDefaultDungeons();
