// FILE: include/GameWorld.h
#pragma once
#include <vector>
#include <string>
#include <map>

namespace Adventure {

struct DungeonProgress {
    bool cleared = false;
    int floorsCleared = 0;
};

class GameWorld {
public:
    GameWorld();
    int day() const;
    void passDays(int days);
    void restAtInn(); // passes 1 day
    void setDungeonCleared(int idx, bool cleared);
    bool isDungeonCleared(int idx) const;
    void setBossCleared(int idx, bool cleared);
    bool isBossCleared(int idx) const;

    // persist/load helpers
    int toSaveDay() const { return day_; }
    void fromLoadDay(int d) { day_ = d; }

private:
    int day_;
    std::map<int, DungeonProgress> dungeons_;
    std::map<int,bool> bossCleared_;
};

} // namespace Adventure
