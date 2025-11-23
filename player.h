#pragma once
#include <string>
#include <vector>

// forward
struct Achievement;

struct PlayerState {
    std::string classId;
    int level = 1;
    int xp = 0;
    int skillPoints = 0;

    int maxHp = 20;
    int hp = 20;
    int attack = 5;
    int defence = 2;

    // permanent bonuses from achievements / training / items
    int permAttackBoost = 0;
    int permDefenceBoost = 0;
    int permHpBoost = 0;

    // temporary battle buffs
    int tempAttackBoost = 0;
    int tempDefenceBoost = 0;
    int tempHpBoost = 0;                // used by loot/items for temp HP
    int tempBuffBattlesRemaining = 0;   // how many battles the temp buffs still last

    std::vector<std::string> unlockedClassSkills;
    std::string currentLocationKey;
    int reviveTokens = 0;
    bool restUsed = false;
};

void levelUp(PlayerState& player);

// Declare applyAchievementsToPlayer so other translation units (game.cpp) can call it
void applyAchievementsToPlayer(PlayerState& player, const std::vector<Achievement>& achievements);
