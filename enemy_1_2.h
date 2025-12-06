// FILE: include/Enemy_1_2.h
#pragma once
#include "Entity.h"
#include "Enums.h"
#include <string>

namespace Adventure {

class Enemy : public Entity {
public:
    Enemy();
    Enemy(std::string name, int baseHp, int baseAtk, int baseDef, int level, EnemyTier tier);
    Enemy(const Enemy& other);
    ~Enemy() override;

    void update() override {}

    int hp() const;
    int atk() const;
    int def() const;
    int level() const;
    EnemyTier tier() const;

    void takeDamage(int dmg);
    bool isDead() const;

    // scaling over world days
    void applyDayScaling(int days);

    // ultimate boss scaling: add 50% of last boss stats
    void applyExtraFromBoss(const Enemy& lastBoss);

    // expose raw stats for save/load
    int baseHp() const;
    int baseAtk() const;
    int baseDef() const;

private:
    int baseHp_;
    int baseAtk_;
    int baseDef_;

    int curHp_;
    int atk_;
    int def_;

    int level_;
    EnemyTier tier_;
};

} // namespace Adventure
