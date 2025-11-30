// FILE: skills_1_2.h
// Complete SkillTree for all classes (starting/advanced/ultimate/hidden).
// Reference: /mnt/data/Document.pdf
#pragma once
#include "enums.h"
#include <string>
#include <vector>
#include <map>

namespace Adventure {

// NOTE: keep this Skill struct compatible with the other modules.
// If you have another Skill struct already, adapt names/fields accordingly.
struct Skill {
    std::string id;           // unique id, e.g. "sum_summon_sprite"
    std::string name;         // display name
    std::string description;  // short description
    int requiredLevel = 1;    // minimum player level
    int cost = 1;             // skill points cost
    int power = 0;            // numeric magnitude: used by BattleEngine
    // type or tags can be added if needed
};

class SkillTree {
public:
    // Singleton-like access (simple static instance)
    static SkillTree& instance();

    // get all skills that a class can learn (includes starting + advanced + ultimate + hidden)
    const std::vector<Skill>& skillsFor(ClassType cls) const;

    // find a skill by id
    const Skill* skillById(const std::string& id) const;

    // check whether a class may learn this skill (based on our mapping)
    bool isSkillAvailableFor(ClassType cls, const std::string& id) const;

    // debugging / listing helpers
    std::vector<std::string> skillIdsFor(ClassType cls) const;

private:
    SkillTree(); // constructs all skill lists
    void buildStarting();
    void buildAdvanced();
    void buildUltimate();
    void buildHidden();

    std::map<ClassType, std::vector<Skill>> table_;
    std::map<std::string, Skill> lookup_;
};

} // namespace Adventure
