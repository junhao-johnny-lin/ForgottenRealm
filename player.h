#pragma once
#include <string>
#include <vector>

struct PlayerState {
    // Stats
    int hp = 100;
    int maxHp = 100;
    int attack = 10;
    int defence = 5;

    // Progressie
    int xp = 0;
    int level = 1;

    // Skill points (alleen voor class skills)
    int skillPoints = 0;
    std::string classId = "warrior"; // warrior|mage|ranger|assassin

    // Run-state
    int reviveTokens = 0;
    int dayCount = 0; // +1 bij inn gebruik
    std::string currentLocationKey = "south_cliffs";

    // Klass skills die gekocht zijn
    std::vector<std::string> unlockedClassSkills;
};

void gainXP(PlayerState& p, int amount);
bool spendSkillPoints(PlayerState& p, int cost);
