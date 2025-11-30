// FILE: src/Dungeon_1_2.cpp
#include "Dungeon_1_2.h"
#include <cstdlib>
#include <sstream>

namespace Adventure {

Dungeon::Dungeon(const std::string& id) : id_(id) {}

void Dungeon::build(int floors, const Enemy& bossPrototype, int regionIndex) {
    floors_.clear();
    for (int f=1; f<=floors; ++f) {
        DungeonFloor df;
        df.floorNumber = f;
        if (f < floors) {
            int count = 1 + (std::rand()%2);
            for (int i=0;i<count;++i) {
                int hp = 8 + f*2 + regionIndex*2;
                int atk = 2 + f/3 + regionIndex/2;
                int def = f/5 + regionIndex/3;
                std::ostringstream os;
                os << id_ << "_mob_" << f << "_" << i;
                df.enemies.emplace_back(os.str(), hp, atk, def, f, EnemyTier::Normal);
            }
        } else {
            df.hasBoss = true;
            // boss: copy prototype but adjust name
            Enemy boss = bossPrototype;
            // ensure boss name contains id
            // already passed in by prototype
            df.enemies.push_back(boss);
        }
        floors_.push_back(df);
    }
}

const std::vector<DungeonFloor>& Dungeon::floors() const { return floors_; }

} // namespace Adventure
