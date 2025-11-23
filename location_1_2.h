// FILE: include/Location.h
#pragma once
#include "Enemy_1_2.h"
#include "Trainer_1_2.h"
#include <vector>
#include <string>

namespace Adventure {

class Location {
public:
    Location() = default;
    Location(std::string id, std::string desc);

    void addEnemy(const Enemy& e);
    void setTrainer(Trainer t);
    const std::string& id() const;
    const std::string& desc() const;
    bool hasDungeon() const;
    void setDungeon(bool v);
    bool hasInn() const;
    void setInn(bool v);
    bool hasTrainer() const;
    Trainer* trainer();
    const std::vector<Enemy>& enemies() const;

    // achievements per location
    void addAchievementId(const std::string& id);
    const std::vector<std::string>& achievementIds() const;

private:
    std::string id_;
    std::string desc_;
    std::vector<Enemy> enemies_;
    Trainer trainer_;
    bool hasTrainer_ = false;
    bool hasDungeon_ = true;
    bool hasInn_ = true;
    std::vector<std::string> achievementIds_;
};

} // namespace Adventure
