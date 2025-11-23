// class_skills.cpp
#include "class_skills.h"
#include <map>
#include <string>
#include <unordered_map>

// rest van implementatie blijft hetzelfde, bijvoorbeeld:
static std::map<std::string, Skill> s_skills = {
    {"evade", {"Quick evade to avoid attacks", "evade", 0, 0, "Evade", true}},
    {"fireball", {"Throws a ball of fire", "fireball", 6, 5, "Fireball", false}},
    {"shield", {"Raise a magical shield", "shield", 0, 3, "Shield", true}},
    {"stab", {"A precise stabbing attack", "stab", 3, 0, "Stab", false}},
    {"strike", {"A heavy melee strike", "strike", 4, 0, "Strike", false}},
    };

const Skill* getSkillById(const std::string& id) {
    auto it = s_skills.find(id);
    if (it == s_skills.end()) return nullptr;
    return &it->second;
}
