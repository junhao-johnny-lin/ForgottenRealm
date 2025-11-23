// loot.h
#pragma once
#include <string>
#include <vector>

struct Potion {
    std::string id;
    std::string name;
    int potency = 1;
    bool permanent = false;
};

std::vector<std::string> generateLootForEnemy(const std::string& enemyId);
std::vector<Potion> convertWeaponToPotions(const std::string& weaponId, int tier, int durability);
