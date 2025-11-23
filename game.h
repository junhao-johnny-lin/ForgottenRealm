#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "map_renderer.h"
#include "player.h"
#include "dungeon.h"
#include "achievements.h"
#include "map2.h"

class Game {
public:
    Game();
    void run();
    // in Game { ... }
    std::unordered_map<std::string, std::string> canonicalKeyByNormalized;
    WorldMap map;

private:
    std::unordered_map<std::string, Location> nodes_;
    std::unordered_map<std::string, Dungeon> dungeons_;
    PlayerState player_;
    std::vector<Achievement> achievements_;

    void initWorld();
    void runIntro();
    void levelUpCmd();

    // save/load
    void saveCmd(const std::string& path);
    void loadCmd(const std::string& path);

    // dungeon
    bool enterDungeon(const std::string& locationKey);
};

