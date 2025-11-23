// FILE: src/GameWorld.cpp
#include "GameWorld.h"

namespace Adventure {

GameWorld::GameWorld() : day_(0) {}

int GameWorld::day() const { return day_; }

void GameWorld::passDays(int days) {
    if (days <= 0) return;
    day_ += days;
}

void GameWorld::restAtInn() {
    ++day_;
}

void GameWorld::setDungeonCleared(int idx, bool cleared) {
    dungeons_[idx].cleared = cleared;
}
bool GameWorld::isDungeonCleared(int idx) const {
    auto it = dungeons_.find(idx);
    return it != dungeons_.end() && it->second.cleared;
}

void GameWorld::setBossCleared(int idx, bool cleared) {
    bossCleared_[idx] = cleared;
}
bool GameWorld::isBossCleared(int idx) const {
    auto it = bossCleared_.find(idx);
    return it != bossCleared_.end() && it->second;
}

} // namespace Adventure
