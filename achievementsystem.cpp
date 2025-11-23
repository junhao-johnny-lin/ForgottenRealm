// FILE: src/AchievementSystem.cpp
#include "AchievementSystem.h"

namespace Adventure {

AchievementSystem::AchievementSystem() {
    // Example achievements per dungeon; for brevity only a few defined; expand as needed
    ach_["hibernia_clear"] = Achievement{"hibernia_clear","Hibernia Conqueror","Clear Hibernia dungeon", 5,2,50,10,false};
    ach_["araluen_clear"] = Achievement{"araluen_clear","Araluen Hero","Clear Araluen dungeon", 3,1,20,5,false};
    // add placeholders for all 18 if needed; here we add programmatically in GameMap as well
}

void AchievementSystem::unlock(const std::string& id) {
    auto it = ach_.find(id);
    if (it != ach_.end()) it->second.unlocked = true;
    else {
        // create a generic achievement if missing
        ach_[id] = Achievement{id, "Achievement "+id, "Cleared "+id, 1,0,10,0,true};
    }
}

bool AchievementSystem::isUnlocked(const std::string& id) const {
    auto it = ach_.find(id);
    return it != ach_.end() && it->second.unlocked;
}

const std::map<std::string, Achievement>& AchievementSystem::all() const { return ach_; }
const Achievement* AchievementSystem::get(const std::string& id) const {
    auto it = ach_.find(id);
    if (it == ach_.end()) return nullptr;
    return &it->second;
}

} // namespace Adventure
