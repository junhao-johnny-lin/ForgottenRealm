#include "items.h"

static std::unordered_map<std::string, WeaponTier> s_weapons = {
    {"iron_sword", {"iron_sword","Iron Sword", 12, Rarity::Common}},
    {"steel_sword", {"steel_sword","Steel Sword", 18, Rarity::Uncommon}},
    {"elven_bow", {"elven_bow","Elven Bow", 22, Rarity::Rare}},
    {"arcane_staff", {"arcane_staff","Arcane Staff", 28, Rarity::Epic}},
    {"dragon_slayer", {"dragon_slayer","Dragon Slayer", 40, Rarity::Legendary}},
    };

static std::unordered_map<std::string, ArmorTier> s_armors = {
    {"leather", {"leather","Leather Armor", 6, Rarity::Common}},
    {"chainmail", {"chainmail","Chainmail", 10, Rarity::Uncommon}},
    {"plate", {"plate","Plate Armor", 16, Rarity::Rare}},
    {"runed_plate", {"runed_plate","Runed Plate", 22, Rarity::Epic}},
    {"dragon_scale", {"dragon_scale","Dragon Scale", 30, Rarity::Legendary}},
    };

const std::unordered_map<std::string, WeaponTier>& getWeaponTiers(){ return s_weapons; }
const std::unordered_map<std::string, ArmorTier>& getArmorTiers(){ return s_armors; }
