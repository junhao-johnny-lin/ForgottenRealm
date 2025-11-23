// battle.h
#pragma once
#include <string>
#include <vector>

struct BattleEvent {
    std::string description;
};

struct Mob {
    std::string id;
    std::string name;
    int hp = 0;
    int attack = 0;
    int defence = 0;
};

struct BattleResult {
    bool playerWon = false;
    std::vector<std::string> loot; // item ids
    std::vector<BattleEvent> events;
};

BattleResult resolveBattle(const std::vector<Mob>& mobs, const std::string& playerClass, int& playerHp);
