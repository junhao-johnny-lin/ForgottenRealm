// FILE: include/AchievementSystem.h
#pragma once
#include "Achievement_1_2.h"
#include <map>
#include <string>

namespace Adventure {

class AchievementSystem {
public:
    AchievementSystem();
    void unlock(const std::string& id);
    bool isUnlocked(const std::string& id) const;
    const std::map<std::string, Achievement>& all() const;
    const Achievement* get(const std::string& id) const;

private:
    std::map<std::string, Achievement> ach_;
};

} // namespace Adventure
