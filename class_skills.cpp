#include "class_skills.h"
#include <algorithm>
#include <iostream>

static std::unordered_map<std::string, std::vector<ClassSkill>> s_classSkills = {
    {"warrior", {
                    {"WARRIOR_SLAM","Shield Slam","+20% damage, stun chance (1 turn)",1,"warrior"},
                    {"WARRIOR_RAGE","Battle Rage","+20% attack for 3 turns",2,"warrior"},
                    {"WARRIOR_IRONWILL","Iron Will","+10% permanent defence",3,"warrior"}
                }},
    {"mage", {
                 {"MAGE_FIREBALL","Fireball","+30% spell damage",1,"mage"},
                 {"MAGE_ARCANE","Arcane Surge","Double mana regen 5 turns",2,"mage"},
                 {"MAGE_ELEMENTAL","Elemental Mastery","+10% all spells",3,"mage"}
             }},
    {"ranger", {
                   {"RANGER_ARROW","Piercing Arrow","Hits multiple enemies",1,"ranger"},
                   {"RANGER_CAMO","Camouflage","Evade first hit in battle",2,"ranger"},
                   {"RANGER_BEAST","Beast Bond","Summon companion",3,"ranger"}
               }},
    {"assassin", {
                     {"ASSASSIN_BACKSTAB","Backstab","Double damage first strike",1,"assassin"},
                     {"ASSASSIN_POISON","Poison Blade","+5 DoT per turn",2,"assassin"},
                     {"ASSASSIN_SHADOWSTEP","Shadowstep","Teleport + guaranteed crit",3,"assassin"}
                 }}
};

const std::unordered_map<std::string, std::vector<ClassSkill>>& getClassSkills(){ return s_classSkills; }

bool buyClassSkill(PlayerState& p, const std::string& skillId) {
    auto itList = s_classSkills.find(p.classId);
    if (itList == s_classSkills.end()) { std::cout << "Onbekende class.\n"; return false; }
    const auto& list = itList->second;
    auto it = std::find_if(list.begin(), list.end(), [&](const ClassSkill& s){ return s.id == skillId; });
    if (it == list.end()) { std::cout << "Skill niet beschikbaar voor class.\n"; return false; }
    if (std::find(p.unlockedClassSkills.begin(), p.unlockedClassSkills.end(), it->id) != p.unlockedClassSkills.end()) {
        std::cout << "Skill al gekocht.\n"; return false;
    }
    if (!spendSkillPoints(p, it->cost)) { std::cout << "Niet genoeg skill points.\n"; return false; }
    p.unlockedClassSkills.push_back(it->id);
    std::cout << "Klass skill gekocht: " << it->name << "\n";
    return true;
}
