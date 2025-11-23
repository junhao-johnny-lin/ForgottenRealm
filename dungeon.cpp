// dungeon.cpp
#include "dungeon.h"
#include <algorithm>

std::vector<Dungeon> getDefaultDungeons() {
    std::vector<Dungeon> v;
    Dungeon d;
    d.id = "beginner_hall";
    d.name = "Beginner Hall";
    d.entranceKey = "d_begin_entrance";
    d.floors = {
        {0, "Floor 1", {"goblin","wolf"}},
        {1, "Floor 2", {"orc","skeleton"}}
    };
    v.push_back(d);
    std::sort(v.begin(), v.end(), [](const Dungeon& a, const Dungeon& b){ return a.id < b.id; });
    return v;
}
