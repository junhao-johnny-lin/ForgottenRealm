#include "loot.h"
#include "enemy.h"
#include <random>
#include <iostream>

std::vector<std::string> generateLootForEnemy(const Enemy& enemy) {
    std::vector<std::string> drops;
    std::mt19937 rng(static_cast<unsigned int>(std::random_device{}()));
    std::uniform_int_distribution<int> dist(1, 100);
    int roll = dist(rng);

    // Branch by category (int) for simple, fast checks.
    // Change to string-based checks (enemy.id) if you prefer.
    if (enemy.category == 0) {
        if (roll <= 10) drops.push_back("common_gem");
        if (roll <= 2)  drops.push_back("rare_fragment");
    } else if (enemy.category == 1) {
        if (roll <= 20) drops.push_back("coin_pouch");
        if (roll <= 5)  drops.push_back("magic_rune");
    } else {
        if (roll <= 5) drops.push_back("strange_essence");
    }
    return drops;
}

void applyLootItemToPlayer(PlayerState& player, const std::string& itemId) {
    if (itemId == "common_gem") {
        player.permAttackBoost += 1;
        std::cout << "Je vond een common_gem: +1 permanent attack\n";
    } else if (itemId == "rare_fragment") {
        player.permHpBoost += 5;
        player.maxHp += 5;
        player.hp += 5;
        std::cout << "Je vond een rare_fragment: +5 max HP\n";
    } else if (itemId == "strange_essence") {
        player.tempHpBoost += 5;
        player.tempBuffBattlesRemaining = 3;
        std::cout << "Je vond strange_essence: +5 temporary HP for 3 battles\n";
    } else if (itemId == "magic_rune") {
        player.permDefenceBoost += 1;
        std::cout << "Je vond een magic_rune: +1 permanent defence\n";
    } else if (itemId == "coin_pouch") {
        std::cout << "Je vond een coin_pouch (purely cosmetic in this stub)\n";
    } else {
        std::cout << "Onbekend item: " << itemId << "\n";
    }

    // keep hp bounded by maxHp
    if (player.hp > player.maxHp) player.hp = player.maxHp;
}
