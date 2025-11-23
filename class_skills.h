#pragma once
#include <string>
#include <unordered_map>
#include <vector>

// Skill definitie
struct Skill {
    std::string id;          // unieke id, bv. "slash"
    std::string name;        // naam, bv. "Slash"
    std::string description; // korte uitleg
    int baseDamage;          // basis damage (optioneel)
    int manaCost;            // mana of resource cost (optioneel)
    bool passive;            // true = passieve skill, false = actieve skill
};

// Geeft alle skills terug
const std::unordered_map<std::string, Skill>& getAllSkills();

// Haal een skill op via id
const Skill* getSkillById(const std::string& id);
