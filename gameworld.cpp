// FILE: src/GameWorld.cpp
#include "GameWorld.h"

namespace Adventure {

GameWorld::GameWorld() : day_(0) {}

int GameWorld::day() const { return day_; }
void GameWorld::passDays(int days) { if (days>0) day_ += days; }
void GameWorld::restAtInn() { ++day_; }

void GameWorld::setDungeonCleared(int idx, bool cleared) { dungeons_[idx].cleared = cleared; }
bool GameWorld::isDungeonCleared(int idx) const {
    auto it = dungeons_.find(idx);
    return it != dungeons_.end() && it->second.cleared;
}

void GameWorld::setBossCleared(int idx, bool cleared) { bossCleared_[idx] = cleared; }
bool GameWorld::isBossCleared(int idx) const {
    auto it = bossCleared_.find(idx);
    return it != bossCleared_.end() && it->second;
}

std::vector<std::string> GameWorld::clearedDungeons() const { return clearedDungeonIds_; }
void GameWorld::markDungeonCleared(const std::string& id) {
    for (auto &s : clearedDungeonIds_) if (s == id) return;
    clearedDungeonIds_.push_back(id);
}

void GameWorld::setLastBossStats(int hp, int atk, int def, int speed) { lastBoss_.hp = hp; lastBoss_.atk = atk; lastBoss_.def = def; lastBoss_.speed = speed; }
int GameWorld::lastBossHp() const { return lastBoss_.hp; }
int GameWorld::lastBossAtk() const { return lastBoss_.atk; }
int GameWorld::lastBossDef() const { return lastBoss_.def; }
int GameWorld::lastBossSpeed() const { return lastBoss_.speed; }

std::map<std::string,bool> GameWorld::achievements() const { return achievementsMap_; }
void GameWorld::forceAchievement(const std::string& id, bool unlocked) { achievementsMap_[id] = unlocked; }

} // namespace Adventure
