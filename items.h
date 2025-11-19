#pragma once
#include <string>
#include <unordered_map>

enum class Rarity { Common, Uncommon, Rare, Epic, Legendary };

struct WeaponTier {
    std::string id;
    std::string name;
    int baseDamage;
    Rarity rarity;
};

struct ArmorTier {
    std::string id;
    std::string name;
    int baseDefence;
    Rarity rarity;
};

const std::unordered_map<std::string, WeaponTier>& getWeaponTiers();
const std::unordered_map<std::string, ArmorTier>& getArmorTiers();
