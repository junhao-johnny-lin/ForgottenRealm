// FILE: include/Achievement.h
#pragma once
#include <string>

namespace Adventure {

struct Achievement {
    std::string id;
    std::string name;
    std::string description;
    // Effects: simple set of numeric boosts (kept generic)
    int bonusAttack = 0;
    int bonusDefense = 0;
    int bonusHp = 0;
    int bonusExpPercent = 0; // e.g., 5 = +5%
    bool unlocked = false;
};

} // namespace Adventure
