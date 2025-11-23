// FILE: include/Skill.h
#pragma once
#include <string>

namespace Adventure {

struct Skill {
    std::string id;
    std::string name;
    std::string description;
    int requiredLevel = 1;
    int cost = 1; // skill points
    int power = 0; // numeric effect
    // effect application is up to BattleEngine (by ID)
};

} // namespace Adventure
