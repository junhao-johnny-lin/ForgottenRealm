#include "enemy.h"

static std::unordered_map<std::string, EnemyType> s_types = {
    // Common
    {"goblin", {"goblin","Goblin", EnemyTier::Common, 60, 8, 2, 15, 0.005, false}},
    {"wolf",   {"wolf","Wolf", EnemyTier::Common, 70, 9, 3, 18, 0.005, false}},
    // Uncommon
    {"orc",    {"orc","Orc", EnemyTier::Uncommon, 120, 16, 6, 35, 0.0075, false}},
    {"bandit_elite", {"bandit_elite","Elite Bandit", EnemyTier::Uncommon, 140, 18, 7, 40, 0.0075, false}},
    // Rare
    {"warg",   {"warg","Warg", EnemyTier::Rare, 200, 25, 10, 60, 0.01, false}},
    {"ranger_rogue", {"ranger_rogue","Rogue Ranger", EnemyTier::Rare, 180, 28, 9, 70, 0.01, false}},
    // Elite
    {"captain", {"captain","Captain", EnemyTier::Elite, 300, 40, 18, 120, 0.0125, false}},
    {"warlock", {"warlock","Warlock", EnemyTier::Elite, 260, 45, 14, 140, 0.0125, false}},
    // Boss (dungeon boss baseline; groei 10% stats en 20% xp per dag)
    {"boss_generic", {"boss_generic","Dungeon Boss", EnemyTier::Boss, 800, 100, 60, 400, 0.0, true}},
    // Legendary
    {"morg_guard", {"morg_guard","Morgarath Guard", EnemyTier::Legendary, 600, 80, 50, 300, 0.02, false}},
    };

const std::unordered_map<std::string, EnemyType>& getEnemyTypes() { return s_types; }
