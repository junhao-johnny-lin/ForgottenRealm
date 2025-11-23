// skills.cpp
#include "skills.h"
#include <algorithm>

std::vector<SkillDef> getAllSkills() {
    std::vector<SkillDef> v = {
                               {"Basic melee strike", "strike", "Strike", 0},
                               {"Fire projectile", "fireball", "Fireball", 1},
                               {"Quick evasive action", "evade", "Evade", 0},
                               };
    std::sort(v.begin(), v.end(), [](const SkillDef& a, const SkillDef& b){ return a.id < b.id; });
    return v;
}
