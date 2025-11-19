#pragma once
#include <string>
#include <unordered_map>

struct Skill {
    std::string id;
    std::string name;
    std::string description;
    int cost; // skill points
};

const std::unordered_map<std::string, Skill>& getTrainerSkills(); // optioneel
