// items.cpp
#include "items.h"
#include <algorithm>

static std::unordered_map<std::string, WeaponTier> s_weapons = {
    {"arcane_staff", {"arcane_staff", "Arcane Staff", 28, Rarity::Epic}},
    {"dragon_slayer", {"dragon_slayer", "Dragon Slayer", 40, Rarity::Legendary}},
    {"elven_bow", {"elven_bow", "Elven Bow", 22, Rarity::Rare}},
    {"iron_sword", {"iron_sword", "Iron Sword", 12, Rarity::Common}},
    {"steel_sword", {"steel_sword", "Steel Sword", 18, Rarity::Uncommon}},
    };

static std::unordered_map<std::string, ArmorTier> s_armors = {
    {"chainmail", {"chainmail", "Chainmail", 10, Rarity::Uncommon}},
    {"dragon_scale", {"dragon_scale", "Dragon Scale", 30, Rarity::Legendary}},
    {"leather", {"leather", "Leather Armor", 6, Rarity::Common}},
    {"plate", {"plate", "Plate Armor", 16, Rarity::Rare}},
    {"runed_plate", {"runed_plate", "Runed Plate", 22, Rarity::Epic}},
    };

const std::unordered_map<std::string, WeaponTier>& getWeaponTiers() { return s_weapons; }
const std::unordered_map<std::string, ArmorTier>& getArmorTiers() { return s_armors; }

// --- helpers ---

int baseDurabilityForTier(int tier) {
    switch (tier) {
    case 1: return 10;
    case 2: return 20;
    case 3: return 35;
    default: return 8 + tier * 7;
    }
}

WeaponInstance makeWeaponInstanceFromTierId(const std::string& tierId,
                                            const std::string& type,
                                            const std::string& allowedClass,
                                            int overrideBaseDamage,
                                            int initialDurability) {
    WeaponInstance wi;
    auto it = s_weapons.find(tierId);
    if (it != s_weapons.end()) {
        const WeaponTier& wt = it->second;
        wi.id = wt.id;
        wi.name = wt.name;
        // map rarity -> tier number
        switch (wt.rarity) {
        case Rarity::Common:    wi.tier = 1; break;
        case Rarity::Uncommon:  wi.tier = 2; break;
        case Rarity::Rare:      wi.tier = 3; break;
        case Rarity::Epic:      wi.tier = 4; break;
        case Rarity::Legendary: wi.tier = 5; break;
        }
        wi.baseDamage = (overrideBaseDamage > 0) ? overrideBaseDamage : wt.baseDamage;
    } else {
        // fallback when unknown tierId
        wi.id = tierId;
        wi.name = tierId;
        wi.tier = 1;
        wi.baseDamage = (overrideBaseDamage > 0) ? overrideBaseDamage : 1;
    }
    wi.type = type;
    wi.allowedClass = allowedClass;
    int maxd = baseDurabilityForTier(wi.tier);
    wi.durability = (initialDurability >= 0) ? std::min(initialDurability, maxd) : maxd;
    return wi;
}
