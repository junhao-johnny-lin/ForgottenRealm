// class_defs.h
#pragma once
#include <string>
#include <vector>

struct ClassDef {
    std::string description;
    std::string id;
    std::string name;
    std::vector<std::string> skills;
};

std::vector<ClassDef> getDefaultClasses();
std::vector<std::string> getApplicableClassesForLocation(const std::string& locationKey);
