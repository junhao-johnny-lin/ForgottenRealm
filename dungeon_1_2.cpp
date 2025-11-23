// FILE: src/Dungeon.cpp
#include "Dungeon_1_2.h"

namespace Adventure {

void Dungeon::build(int floors, const Enemy& bossPrototype, int areaIndex) {
    floors_.clear();
    for (int i = 1; i <= floors; ++i) {
        DungeonFloor f;
        f.floorNumber = i;
        int enemiesCount = 2 + (i / 2); // more enemies on higher floors
        for (int e = 0; e < enemiesCount; ++e) {
            Enemy en("Grunt_" + std::to_string(i) + "_" + std::to_string(e), 8 + i * 3, 2 + i/2, i, EnemyTier::Normal);
            f.enemies.push_back(en);
        }
        if (i == floors) {
            f.hasBoss = true;
            f.enemies.clear();
            // bossPrototype passed in is used; copy it but can adjust name
            Enemy boss = bossPrototype;
            boss = Enemy(bossPrototype.name() + " (Boss)", bossPrototype.hp(), bossPrototype.atk(), bossPrototype.level(), EnemyTier::Boss);
            f.enemies.push_back(boss);
        }
        floors_.push_back(f);
    }
}

const std::vector<DungeonFloor>& Dungeon::floors() const { return floors_; }
const std::string& Dungeon::id() const { return id_; }

} // namespace Adventure
