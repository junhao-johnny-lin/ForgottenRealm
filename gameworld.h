// FILE: include/GameWorld.h
#pragma once
#include <string>
#include <vector>
#include <map>

namespace Adventure {

struct DungeonProgress {
    bool cleared = false;
    int floorsCleared = 0;
};

struct LastBossStats {
    int hp = 0;
    int atk = 0;
    int def = 0;
    int speed = 0;
};

class GameWorld {
public:
    GameWorld();

    int day() const;
    void passDays(int days);
    void restAtInn();

    void setDungeonCleared(int idx, bool cleared);
    bool isDungeonCleared(int idx) const;

    void setBossCleared(int idx, bool cleared);
    bool isBossCleared(int idx) const;

    std::vector<std::string> clearedDungeons() const;
    void markDungeonCleared(const std::string& id);

    void setLastBossStats(int hp, int atk, int def, int speed);
    int lastBossHp() const;
    int lastBossAtk() const;
    int lastBossDef() const;
    int lastBossSpeed() const;

    std::map<std::string,bool> achievements() const;
    void forceAchievement(const std::string& id, bool unlocked);

    // compatibility helpers used by SaveSystem
    void fromLoadDay(int d) { day_ = d; }

private:
    int day_;
    std::map<int, DungeonProgress> dungeons_;
    std::map<int,bool> bossCleared_;
    std::vector<std::string> clearedDungeonIds_;
    LastBossStats lastBoss_;
    std::map<std::string,bool> achievementsMap_;
};

} // namespace Adventure
