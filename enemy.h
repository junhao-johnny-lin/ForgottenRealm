#pragma once
#include <string>
#include <unordered_map>

enum class EnemyTier { Common, Uncommon, Rare, Elite, Boss, UltimateBoss, Legendary };

struct EnemyType {
    std::string id;
    std::string name;
    EnemyTier tier;
    int baseHp;
    int baseAttack;
    int baseDefence;
    int baseXP;
    double growthFactor; // per dag (niet voor Boss/UltimateBoss)
    bool isBoss = false;
};

const std::unordered_map<std::string, EnemyType>& getEnemyTypes();
