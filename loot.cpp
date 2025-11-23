// loot.cpp
#include "loot.h"
#include "items.h"
#include <vector>
#include <string>

std::vector<std::string> generateLootForEnemy(const std::string& /*enemyId*/) {
    return { "iron_sword" };
}

std::vector<Potion> convertWeaponToPotions(const std::string& weaponId, int tier, int /*durability*/) {
    std::vector<Potion> out;
    Rarity rarity = Rarity::Common;
    auto it = getWeaponTiers().find(weaponId);
    if (it != getWeaponTiers().end()) rarity = it->second.rarity;

    int tempCount = 1;
    bool perm = false;
    switch (rarity) {
    case Rarity::Common: tempCount = 1; break;
    case Rarity::Uncommon: tempCount = 2; break;
    case Rarity::Rare: tempCount = 3; break;
    case Rarity::Epic: tempCount = 5; break;
    case Rarity::Legendary: tempCount = 8; perm = true; break;
    }

    for (int i = 0; i < tempCount; ++i) {
        Potion p;
        p.id = "pot_temp_t" + std::to_string(tier);
        p.name = "Temporary Potion (tier " + std::to_string(tier) + ")";
        p.potency = std::max(1, tier);
        p.permanent = false;
        out.push_back(p);
    }
    if (perm) {
        Potion p;
        p.id = "pot_perm_t" + std::to_string(tier);
        p.name = "Permanent Potion (tier " + std::to_string(tier) + ")";
        p.potency = std::max(1, tier + 1);
        p.permanent = true;
        out.push_back(p);
    }
    return out;
}
