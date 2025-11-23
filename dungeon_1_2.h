// FILE: include/Dungeon.h
#pragma once
#include "Enemy_1_2.h"
#include <vector>
#include <string>

namespace Adventure {

struct DungeonFloor {
    int floorNumber = 0;
    std::vector<Enemy> enemies;
    bool hasBoss = false;
};

class Dungeon {
public:
    Dungeon() = default;
    explicit Dungeon(std::string id) : id_(std::move(id)) {}

    void build(int floors, const Enemy& bossPrototype, int areaIndex);
    const std::vector<DungeonFloor>& floors() const;
    const std::string& id() const;

private:
    std::string id_;
    std::vector<DungeonFloor> floors_;
};

} // namespace Adventure
