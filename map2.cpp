// map2.cpp
#include "map2.h"

GameMap loadDefaultMap() {
    GameMap m;
    m.name = "Overland";
    m.width = 40;
    m.height = 10;
    m.nodes = {
               {"village", "Village", 2, 2},
               {"forest", "Forest", 10, 3},
               {"dungeon_entrance", "Dungeon Entrance", 20, 5},
               };
    m.heroLocationKey = "village";
    return m;
}
