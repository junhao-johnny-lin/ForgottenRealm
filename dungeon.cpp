#include "dungeon.h"
Dungeon makeDungeon(const std::string& id, const std::string& name, const std::string& entranceKey, int floors) {
    Dungeon d;
    d.id = id;
    d.name = name;
    d.entranceKey = entranceKey;
    d.floorsCount = floors;
    for (int i = 1; i <= floors; ++i) {
        DungeonFloor f;
        f.floorIndex = i;
        f.label = "Floor " + std::to_string(i);
        f.encounterCount = 2 + (i - 1);
        f.hasBoss = (i == floors);
        d.floors.push_back(f);
    }
    return d;
}
