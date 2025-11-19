#include "battle.h"
#include <iostream>
#include <algorithm>

int scaleDailyStat(int base, double percentPerDay, int days) {
    double factor = 1.0 + percentPerDay * days;
    return static_cast<int>(base * factor);
}

int scaleDailyXP(int baseXP, double percentPerDay, int days) {
    double factor = 1.0 + percentPerDay * days;
    return static_cast<int>(baseXP * factor);
}

// Boss: +10% stats/day, +20% XP/day
EnemyType makeScaledDungeonBoss(const EnemyType& bossBase, int daysSince) {
    EnemyType e = bossBase;
    e.baseHp      = scaleDailyStat(bossBase.baseHp, 0.10, daysSince);
    e.baseAttack  = scaleDailyStat(bossBase.baseAttack, 0.10, daysSince);
    e.baseDefence = scaleDailyStat(bossBase.baseDefence, 0.10, daysSince);
    e.baseXP      = scaleDailyXP(bossBase.baseXP, 0.20, daysSince);
    return e;
}

// Ultimate Boss: 150% van laatste boss +5% stats/dag, +10% XP/dag
BossStats generateUltimateBoss(const EnemyType& lastBossBase, int daysSince) {
    double statFactor = 1.5 * (1.0 + 0.05 * daysSince);
    double xpFactor   = (1.0 + 0.10 * daysSince);
    BossStats ub;
    ub.hp      = static_cast<int>(lastBossBase.baseHp     * statFactor);
    ub.attack  = static_cast<int>(lastBossBase.baseAttack * statFactor);
    ub.defence = static_cast<int>(lastBossBase.baseDefence* statFactor);
    ub.xp      = static_cast<int>(lastBossBase.baseXP     * xpFactor);
    return ub;
}

CombatResult fight(PlayerState& p, const EnemyType& e) {
    int enemyHP = e.baseHp;
    int enemyATK = e.baseAttack;
    int enemyDEF = e.baseDefence;

    int playerHP = p.hp;
    int playerATK = p.attack;
    int playerDEF = p.defence;

    int round = 0;
    while (playerHP > 0 && enemyHP > 0 && round < 1000) {
        // speler valt aan
        int dmgToEnemy = std::max(1, playerATK - enemyDEF/2);
        enemyHP -= dmgToEnemy;
        // enemy valt aan
        if (enemyHP > 0) {
            int dmgToPlayer = std::max(1, enemyATK - playerDEF/2);
            playerHP -= dmgToPlayer;
        }
        round++;
    }

    CombatResult res;
    if (enemyHP <= 0 && playerHP > 0) {
        p.hp = std::max(1, playerHP);
        res.playerWon = true;
        res.xpEarned = e.baseXP;
        std::cout << "Gevecht gewonnen. XP +" << res.xpEarned << "\n";
    } else {
        p.hp = std::max(0, playerHP);
        res.playerWon = false;
        res.xpEarned = 0;
        std::cout << "Gevecht verloren.\n";
    }
    return res;
}
