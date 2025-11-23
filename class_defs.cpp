#include "class_defs.h"

static std::unordered_map<std::string, ClassDef> g_classes;

const std::unordered_map<std::string, ClassDef>& getAllClasses() {
    if (g_classes.empty()) {
        ClassDef warrior{"warrior","Warrior","Brute fighter",30,7,3,{"bash","guard"}};
        ClassDef ranger{"ranger","Ranger","Ranged skirmisher",22,6,2,{"aim","evade"}};
        ClassDef mage{"mage","Mage","Spellcaster",18,8,1,{"spark","shield"}};
        g_classes.emplace(warrior.id, warrior);
        g_classes.emplace(ranger.id, ranger);
        g_classes.emplace(mage.id, mage);
    }
    return g_classes;
}

std::vector<std::string> getApplicableClassesForLocation(const std::string& locationKey) {
    // simple mapping by location prefix (customize as you like)
    if (locationKey == "araluen" || locationKey == "redmont") return {"warrior","ranger"};
    if (locationKey == "celtica" || locationKey == "fens") return {"ranger","mage"};
    return {"warrior","ranger","mage"};
}
