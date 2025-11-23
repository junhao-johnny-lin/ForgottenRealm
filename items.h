// items.h
#pragma once
#include <string>
#include <unordered_map>
#include <vector>

enum class Rarity { Common, Epic, Legendary, Rare, Uncommon };

struct ArmorTier {
    std::string id;
    std::string name;
    int baseDefence;
    Rarity rarity;
};

struct WeaponTier {
    std::string id;
    std::string name;
    int baseDamage;
    Rarity rarity;
};

// Lightweight runtime weapon instance (keeps state zoals durability)
struct WeaponInstance {
    std::string id;            // matches WeaponTier.id, e.g. "iron_sword"
    std::string type;          // optional: "sword", "club", etc.
    std::string name;          // display name (filled from tier)
    int tier = 1;              // derived from rarity mapping
    int baseDamage = 1;        // copied from tier
    int durability = 0;        // current durability ( <= maxDurabilityForTier(tier) )
    std::string allowedClass;  // empty = usable by all
};

const std::unordered_map<std::string, WeaponTier>& getWeaponTiers();
const std::unordered_map<std::string, ArmorTier>& getArmorTiers();

int baseDurabilityForTier(int tier);

WeaponInstance makeWeaponInstanceFromTierId(const std::string& tierId,
                                            const std::string& type = "generic",
                                            const std::string& allowedClass = "",
                                            int overrideBaseDamage = -1,
                                            int initialDurability = -1);
