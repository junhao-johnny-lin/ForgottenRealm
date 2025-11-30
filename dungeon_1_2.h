// FILE: include/Dungeon_1_2.h
#pragma once
#include <string>
#include <vector>
#include "Enemy_1_2.h"

namespace Adventure {

struct DungeonFloor {
    int floorNumber = 0;
    std::vector<Enemy> enemies;
    bool hasBoss = false;
};

class Dungeon {
public:
    Dungeon() = default;
    explicit Dungeon(const std::string& id);

    void build(int floors, const Enemy& bossPrototype, int regionIndex);
    const std::vector<DungeonFloor>& floors() const;

private:
    std::string id_;
    std::vector<DungeonFloor> floors_;
};

} // namespace Adventure
