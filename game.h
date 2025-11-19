#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "map_renderer.h"
#include "achievements.h"
#include "player.h"
#include "enemy.h"

class Game {
public:
    Game();
    void runLoop();
    void handleCommand(const std::string& cmd);

private:
    std::unordered_map<std::string, Location> nodes_;
    std::vector<std::string> tpl_;
    PlayerState player_;
    std::vector<Achievement> achievements_;

    // Laatste NIEUWE dungeon boss kill (geen reruns) en de dag van die kill
    std::string lastNewDungeonBossId_;
    int lastBossKillDay_ = 0;

    void cmdMap(bool full);
    void cmdWhere() const;
    void cmdLook() const;
    void cmdInn(); // dag +1
    void cmdFight(const std::string& enemyId);
    void cmdBossFight(); // scaled boss
    void cmdUltimate(); // hibernia ultimate boss
    void cmdSkillsList() const;
    void cmdBuyClassSkill(const std::string& id);
    void cmdSave(const std::string& path) const;
    void cmdLoad(const std::string& path);
};
