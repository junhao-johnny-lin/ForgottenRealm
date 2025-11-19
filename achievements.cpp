#include "achievements.h"
#include <algorithm>

std::vector<Achievement> getDefaultAchievements() {
    std::vector<Achievement> v = {
        {"ACH_FIRSTBLOOD","First Blood","Versla je eerste vijand", false, StatMods{0,1,0,0,0,0}, {}},
        {"ACH_BOSS_CONQUEROR","Boss Conqueror","Versla je eerste Boss", false, StatMods{0,1,0,0,0,0}, {{"boss_drop_guarantee",1}}},
        {"ACH_ELITE_SLAYER","Elite Slayer","Versla 50 Elites", false, StatMods{0,3,0,0,0,0}, {{"drop_rate_boost_percent",5}}},
        {"ACH_EXPLORER","Explorer","Bezoek 10 locaties", false, StatMods{0,0,0,0,1,0}, {}},
        {"ACH_PERSISTENCE","Grinder","Verzamel 500 kills in één sessie", false, StatMods{2,0,0,0,0,0}, {}}
    };
    return v;
}

bool unlockAchievement(std::vector<Achievement>& list, const std::string& id) {
    auto it = std::find_if(list.begin(), list.end(), [&](const Achievement &a){ return a.id==id;});
    if (it == list.end() || it->unlocked) return false;
    it->unlocked = true;
    return true;
}
