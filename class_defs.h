#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct ClassDef {
    std::string id;
    std::string name;
    std::string description;
    int baseHP = 20;
    int baseAttack = 5;
    int baseDefense = 2;
    std::vector<std::string> skills;
};

const std::unordered_map<std::string, ClassDef>& getAllClasses();
std::vector<std::string> getApplicableClassesForLocation(const std::string& locationKey);
