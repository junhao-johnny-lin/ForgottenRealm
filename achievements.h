#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct StatMods {
    int hp = 0;
    int strength = 0;
    int defence = 0;
    int mana = 0;
    int speed = 0;
    int intelligence = 0;
};

struct Achievement {
    std::string id;
    std::string name;
    std::string description;
    bool unlocked = false;
    StatMods mods;
    std::unordered_map<std::string,int> flags;
};

std::vector<Achievement> getDefaultAchievements();
bool unlockAchievement(std::vector<Achievement>& list, const std::string& id);
