// FILE: include/Enums.h
#pragma once
#include <string>

namespace Adventure {

enum class ItemType { Generic=0, Weapon=1, Armor=2 };
enum class ItemRarity { Common=0, Rare=1, Epic=2, Legendary=3 };

// Class categories
enum class ClassTier { Starting=0, Advanced=1, Ultimate=2, Hidden=3 };

enum class ClassType {
    Knight, Paladin, Mage, Cleric,
    Ranger, Druid, Scout, Alchemist,
    Berserker, Lancer, MountainDweller, Summoner,
    // advanced/ultimate/hidden placeholders - can map progression
    ArcaneKnight, BattleMage, HighPriest, Beastmaster, Shaman, SpearMaster,
    Spellblade, Spellbreaker, MountainWarden, DeathKnight, Archdruid, Witch,
    Elementalist, Necromancer, Psion, WyvernRider, Shadowmaster, ArcaneArchon,
    DivineHerald, NatureFury, PhantomStalker, EldritchAlchemist, Warbringer,
    SkyReaper, Earthwarden, VoidConjuror, DarkInquisitor, Dreamwalker
};

inline std::string classTypeToString(ClassType c) {
    switch(c){
    case ClassType::Knight: return "Knight";
    case ClassType::Paladin: return "Paladin";
    case ClassType::Mage: return "Mage";
    case ClassType::Cleric: return "Cleric";
    case ClassType::Ranger: return "Ranger";
    case ClassType::Druid: return "Druid";
    case ClassType::Scout: return "Scout";
    case ClassType::Alchemist: return "Alchemist";
    case ClassType::Berserker: return "Berserker";
    case ClassType::Lancer: return "Lancer";
    case ClassType::MountainDweller: return "MountainDweller";
    case ClassType::Summoner: return "Summoner";
    default: return "Advanced/Ultimate/Hidden";
    }
}

} // namespace Adventure
