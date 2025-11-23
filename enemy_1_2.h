// FILE: include/Enemy.h
#pragma once
#include "Entity.h"
#include <string>

namespace Adventure {

enum class EnemyTier { Normal=0, Epic=1, Boss=2, UltimateBoss=3 };

class Enemy : public Entity {
public:
    Enemy();
    Enemy(std::string name, int hp, int atk, int level = 1, EnemyTier tier = EnemyTier::Normal);

    void update() override {}
    int atk() const { return atk_; }
    int hp() const { return hp_; }
    int level() const { return level_; }
    EnemyTier tier() const { return tier_; }
    void takeDamage(int d) { hp_ -= d; }
    bool isDead() const { return hp_ <= 0; }

    // scale stats using day and rules (see GameWorld)
    void applyDayScaling(int days, bool prevBossUncleared);

private:
    int hp_;
    int atk_;
    int level_;
    EnemyTier tier_;
};

} // namespace Adventure
