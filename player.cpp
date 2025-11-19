#include "player.h"
#include <iostream>

static int xpNeededForLevel(int level) {
    // eenvoudige curve: 100 * level
    return level * 100;
}

void gainXP(PlayerState& p, int amount) {
    p.xp += amount;
    while (p.xp >= xpNeededForLevel(p.level)) {
        p.xp -= xpNeededForLevel(p.level);
        p.level++;
        p.skillPoints++;
        std::cout << "Level up naar " << p.level << " — skill point +1\n";
        // kleine boost bij level up
        p.maxHp += 5;
        p.hp = p.maxHp;
    }
}

bool spendSkillPoints(PlayerState& p, int cost) {
    if (p.skillPoints < cost) return false;
    p.skillPoints -= cost;
    return true;
}
