#pragma once
#include "enemy.h"
#include "player.h"

struct CombatResult {
    bool playerWon;
    int xpEarned;
};

int scaleDailyStat(int base, double percentPerDay, int days);
int scaleDailyXP(int baseXP, double percentPerDay, int days);

EnemyType makeScaledDungeonBoss(const EnemyType& bossBase, int daysSince);
struct BossStats { int hp; int attack; int defence; int xp; };
BossStats generateUltimateBoss(const EnemyType& lastBossBase, int daysSince);

CombatResult fight(PlayerState& p, const EnemyType& e);
