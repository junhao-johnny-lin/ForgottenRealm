// skills.h
#pragma once
#include <string>
#include <vector>

struct SkillDef {
    std::string description;
    std::string id;
    std::string name;
    int cost = 0; // skill points
};

std::vector<SkillDef> getAllSkills();
