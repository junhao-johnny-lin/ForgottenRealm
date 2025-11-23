// FILE: include/GameEngine.h
#pragma once
#include "GameMap.h"
#include "Player_1_2.h"
#include "BattleEngine.h"
#include "gameworld.h"
#include "AchievementSystem.h"

namespace Adventure {

class GameEngine {
public:
    GameEngine();
    void run();

private:
    GameMap map_;
    Player player_;
    BattleEngine be_;
    GameWorld world_;
    AchievementSystem achievements_;

    void showMainMenu();
    void randomEncounter();
    void enterDungeon();
    void visitTrainer();
    void travel();
    void save();
    void load();
    void restAtInn();
    void checkAndApplyAchievement(const std::string& aid);
    void giveDungeonRewardAndAchievement(int idx);
};

} // namespace Adventure
