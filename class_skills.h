#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "player.h"

struct ClassSkill {
    std::string id;
    std::string name;
    std::string description;
    int cost;
    std::string classId; // warrior|mage|ranger|assassin
};

const std::unordered_map<std::string, std::vector<ClassSkill>>& getClassSkills();
bool buyClassSkill(PlayerState& p, const std::string& skillId);
