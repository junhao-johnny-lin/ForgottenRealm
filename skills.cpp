#include "skills.h"

static std::unordered_map<std::string, Skill> s_trainer = {
    {"TR_POWER_STRIKE", {"TR_POWER_STRIKE","Power Strike","+10% attack",1}},
    {"TR_IRON_SKIN", {"TR_IRON_SKIN","Iron Skin","+10% defence",1}},
    {"TR_FLEETFOOT", {"TR_FLEETFOOT","Fleetfoot","+10% dodge chance",2}},
    {"TR_BOSS_SLAYER", {"TR_BOSS_SLAYER","Boss Slayer","+10% damage vs Boss/Ultimate",4}}
};

const std::unordered_map<std::string, Skill>& getTrainerSkills(){ return s_trainer; }
