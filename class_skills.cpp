#include "class_skills.h"

const std::unordered_map<std::string, Skill>& getAllSkills() {
    static std::unordered_map<std::string, Skill> skills = {
        {"slash",       {"slash", "Slash", "Een snelle aanval met je zwaard.", 10, 0, false}},
        {"block",       {"block", "Block", "Verhoogt je verdediging tijdelijk.", 0, 0, false}},
        {"parry",       {"parry", "Parry", "Kans om een aanval volledig te ontwijken.", 0, 0, false}},
        {"riposte",     {"riposte", "Riposte", "Counter‑aanval na een succesvolle parry.", 15, 0, false}},
        {"holy_strike", {"holy_strike", "Holy Strike", "Een krachtige aanval met heilige energie.", 25, 5, false}},

        {"aim",         {"aim", "Aim", "Verhoogt je crit‑chance voor 1 beurt.", 0, 0, false}},
        {"multi_shot",  {"multi_shot", "Multi Shot", "Schiet meerdere pijlen tegelijk.", 12, 3, false}},
        {"evasion",     {"evasion", "Evasion", "Verhoogt je dodge‑chance tijdelijk.", 0, 0, false}},
        {"rapid_fire",  {"rapid_fire", "Rapid Fire", "Snelle reeks pijlen.", 20, 4, false}},
        {"nature_bond", {"nature_bond", "Nature Bond", "Passive: verhoogt resistances tegen beasts.", 0, 0, true}},

        {"heal",        {"heal", "Heal", "Herstel een deel van je HP.", -15, 5, false}}, // negatieve damage = healing
        {"root",        {"root", "Root", "Vertraagt de vijand.", 0, 3, false}},
        {"regen",       {"regen", "Regeneration", "Passive: herstel HP per beurt.", 0, 0, true}},
        {"wrath",       {"wrath", "Wrath", "Krachtige natuur‑aanval.", 18, 4, false}},
        {"earth_guard", {"earth_guard", "Earth Guard", "Passive: verhoogt je DEF permanent.", 0, 0, true}}
    };
    return skills;
}

const Skill* getSkillById(const std::string& id) {
    const auto& skills = getAllSkills();
    auto it = skills.find(id);
    if (it != skills.end()) return &it->second;
    return nullptr;
}
