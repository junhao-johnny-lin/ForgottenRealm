// enemy.cpp
#include "enemy.h"
#include <algorithm>

static std::vector<Enemy> s_defaultEnemies = {
    {"goblin","Goblin", 8, 2, 0, {"iron_sword"}},
    {"orc","Orc", 16, 4, 1, {"chainmail"}},
    {"skeleton","Skeleton", 10, 3, 0, {"bone_shard"}}
};

const std::vector<Enemy>& getDefaultEnemies() {
    static bool sorted = false;
    if (!sorted) {
        std::sort(s_defaultEnemies.begin(), s_defaultEnemies.end(), [](const Enemy& a, const Enemy& b){ return a.id < b.id; });
        sorted = true;
    }
    return s_defaultEnemies;
}
