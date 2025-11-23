// battle.cpp
#include "battle.h"
#include <algorithm>
#include <iostream>

static void simpleResolveRound(std::vector<Mob>& mobs, int& playerHp, int playerAttack) {
    // player hits first mob if any
    if (!mobs.empty()) {
        mobs[0].hp -= playerAttack;
    }
    // mobs retaliate
    for (const auto& m : mobs) {
        if (m.hp > 0) playerHp -= std::max(0, m.attack - 0);
    }
}

BattleResult resolveBattle(const std::vector<Mob>& mobsIn, const std::string& playerClass, int& playerHp) {
    BattleResult res;
    std::vector<Mob> mobs = mobsIn;
    int playerAttack = 3;
    if (playerClass == "warrior") playerAttack += 2;
    while (playerHp > 0 && std::any_of(mobs.begin(), mobs.end(), [](const Mob& m){ return m.hp > 0; })) {
        simpleResolveRound(mobs, playerHp, playerAttack);
    }
    res.playerWon = playerHp > 0;
    if (res.playerWon) {
        for (const auto& m : mobs) {
            if (m.hp <= 0) {
                res.loot.push_back("common_loot");
                res.events.push_back({ "Defeated " + m.name });
            }
        }
    } else {
        res.events.push_back({ "Player was defeated" });
    }
    return res;
}
