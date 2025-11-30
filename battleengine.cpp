// FILE: src/BattleEngine.cpp
#include "BattleEngine.h"
#include <iostream>
#include <cstdlib>

namespace Adventure {

bool BattleEngine::fight(Player& p, Enemy& e) {
    std::cout << "Battle start: " << p.name() << " vs " << e.name() << "\n";
    // simple turn-based: player attacks first each round
    while (p.isAlive() && !e.isDead()) {
        // player attack
        int patk = p.atk();
        std::cout << p.name() << " hits for " << patk << "\n";
        e.takeDamage(patk);
        if (e.isDead()) break;

        // enemy attack
        int eatk = e.atk();
        std::cout << e.name() << " hits for " << eatk << "\n";
        p.takeDamage(eatk);
    }

    bool playerWon = p.isAlive() && e.isDead();
    if (playerWon) {
        std::cout << "You defeated " << e.name() << "!\n";
        // basic rewards: xp
        p.gainExp(10 + e.level()*5);
        p.addSkillPoints(0); // placeholder
    } else {
        std::cout << "You were defeated by " << e.name() << "\n";
    }
    return playerWon;
}

} // namespace Adventure
