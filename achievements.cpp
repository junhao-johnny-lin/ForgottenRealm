// achievements.cpp
#include "achievements.h"
#include <algorithm>

std::vector<Achievement> getDefaultAchievements() {
    std::vector<Achievement> v = {
                                  {"Defeat the first enemy", "first_kill", "First Kill", false},
                                  {"Complete the first dungeon", "first_dungeon", "Dungeon Initiate", false},
                                  {"Find a legendary item", "legend_item", "Fortune Finder", false},
                                  {"Reach level 5", "level_5", "Acolyte", false},
                                  };
    std::sort(v.begin(), v.end(), [](const Achievement& a, const Achievement& b){
        return a.id < b.id;
    });
    return v;
}

bool unlockAchievement(std::vector<Achievement>& list, const std::string& id) {
    auto it = std::find_if(list.begin(), list.end(), [&](const Achievement& a){ return a.id == id; });
    if (it == list.end()) return false;
    if (it->unlocked) return false;
    it->unlocked = true;
    return true;
}
