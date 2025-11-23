// class_defs.cpp
#include "class_defs.h"
#include <algorithm>

std::vector<ClassDef> getDefaultClasses() {
    std::vector<ClassDef> v = {
                               {"Brutal melee fighter", "warrior", "Warrior", {"strike","block"}},
                               {"Master of subtle attacks", "rogue", "Rogue", {"stab","evade"}},
                               {"Spellcaster who manipulates mana", "mage", "Mage", {"fireball","shield"}},
                               };
    std::sort(v.begin(), v.end(), [](const ClassDef& a, const ClassDef& b){
        return a.id < b.id;
    });
    return v;
}

std::vector<std::string> getApplicableClassesForLocation(const std::string& /*locationKey*/) {
    // default: all classes applicable
    std::vector<std::string> r = {"mage","rogue","warrior"};
    std::sort(r.begin(), r.end());
    return r;
}
