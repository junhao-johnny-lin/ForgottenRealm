// FILE: src/Enemy_1_2.cpp
#include "Enemy_1_2.h"

namespace Adventure {

static int roundToInt(double x) {
    return int(x + 0.5);     // geen cmath nodig
}

Enemy::Enemy()
    : Entity("Enemy"), baseHp_(10), baseAtk_(1), baseDef_(0),
    curHp_(10), atk_(1), def_(0), level_(1), tier_(EnemyTier::Normal) {}

Enemy::Enemy(std::string name, int baseHp, int baseAtk, int baseDef, int level, EnemyTier tier)
    : Entity(std::move(name)), baseHp_(baseHp), baseAtk_(baseAtk), baseDef_(baseDef),
    curHp_(baseHp), atk_(baseAtk), def_(baseDef), level_(level), tier_(tier) {}

Enemy::Enemy(const Enemy& other) = default;
Enemy::~Enemy() = default;

int Enemy::hp() const { return curHp_; }
int Enemy::atk() const { return atk_; }
int Enemy::def() const { return def_; }
int Enemy::level() const { return level_; }
EnemyTier Enemy::tier() const { return tier_; }

void Enemy::takeDamage(int d) { curHp_ -= d; if (curHp_ < 0) curHp_ = 0; }
bool Enemy::isDead() const { return curHp_ <= 0; }

int Enemy::baseHp() const { return baseHp_; }
int Enemy::baseAtk() const { return baseAtk_; }
int Enemy::baseDef() const { return baseDef_; }

void Enemy::applyDayScaling(int days) {
    if (days <= 0) return;

    double hpMul = 1.0, atkMul = 1.0, defMul = 1.0;

    switch (tier_) {
    case EnemyTier::Normal:       hpMul += 0.01 * days; atkMul += 0.01 * days; defMul += 0.01 * days; break;
    case EnemyTier::Epic:         hpMul += 0.05 * days; atkMul += 0.05 * days; defMul += 0.05 * days; break;
    case EnemyTier::Boss:         hpMul += 0.15 * days; atkMul += 0.15 * days; defMul += 0.15 * days; break;
    case EnemyTier::UltimateBoss: hpMul += 0.01 * days; atkMul += 0.01 * days; defMul += 0.01 * days; break;
    }

    atk_   = roundToInt(baseAtk_ * atkMul);
    def_   = roundToInt(baseDef_ * defMul);
    curHp_ = roundToInt(baseHp_ * hpMul);
}

void Enemy::applyExtraFromBoss(const Enemy& lastBoss) {
    atk_   += roundToInt(0.5 * lastBoss.atk());
    def_   += roundToInt(0.5 * lastBoss.def());
    curHp_ += roundToInt(0.5 * lastBoss.hp());
}

} // namespace Adventure
