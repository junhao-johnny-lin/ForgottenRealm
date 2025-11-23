// class_skills.h
#pragma once
#include <string>

struct Skill {
    std::string description;
    std::string id;
    int baseDamage = 0;
    int manaCost = 0;
    std::string name;
    bool passive = false;
};

const Skill* getSkillById(const std::string& id);
