#include "trainer.h"
#include <iostream>

void openTrainer(PlayerState& player, const std::unordered_map<std::string, ClassDef>&) {
    std::cout << "Trainer (stub) — Skill points: " << player.skillPoints << "\n";
    if (player.skillPoints > 0) {
        player.skillPoints -= 1;
        player.permAttackBoost += 1;
        std::cout << "Je besteedt 1 skill point: +1 permanent attack\n";
    } else {
        std::cout << "Geen skill points beschikbaar.\n";
    }
}
