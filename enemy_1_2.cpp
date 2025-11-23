// FILE: src/Enemy.cpp
#include "Enemy_1_2.h"
#include <cmath>

namespace Adventure {

Enemy::Enemy() : Entity("Enemy"), hp_(10), atk_(1), level_(1), tier_(EnemyTier::Normal) {}
Enemy::Enemy(std::string name, int hp, int atk, int level, EnemyTier tier)
    : Entity(std::move(name)), hp_(hp), atk_(atk), level_(level), tier_(tier) {}

void Enemy::applyDayScaling(int days, bool prevBossUncleared) {
    if (days <= 0) return;
    double hpMul = 1.0, atkMul = 1.0;
    switch (tier_) {
    case EnemyTier::Normal:
        hpMul += 0.01 * days;
        atkMul += 0.01 * days;
        break;
    case EnemyTier::Epic:
        hpMul += 0.05 * days;
        atkMul += 0.05 * days;
        break;
    case EnemyTier::Boss:
        hpMul += 0.15 * days;
        atkMul += 0.15 * days;
        break;
    case EnemyTier::UltimateBoss:
        hpMul += 0.01 * days;
        atkMul += 0.01 * days;
        if (prevBossUncleared) { hpMul *= 1.5; atkMul *= 1.5; } // +50% extra
        break;
    }
    hp_ = static_cast<int>(std::ceil(hp_ * hpMul));
    atk_ = static_cast<int>(std::ceil(atk_ * atkMul));
}

} // namespace Adventure
