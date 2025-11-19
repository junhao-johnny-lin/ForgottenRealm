#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "map_renderer.h"
#include "achievements.h"
#include "player.h"

bool saveGameState(const std::string& path,
                   const std::unordered_map<std::string, Location>& nodes,
                   const std::vector<Achievement>& achievements,
                   const PlayerState& player,
                   const std::string& lastNewDungeonBossId,
                   int lastBossKillDay);

bool loadGameState(const std::string& path,
                   std::unordered_map<std::string, Location>& nodes,
                   std::vector<Achievement>& achievements,
                   PlayerState& player,
                   std::string& lastNewDungeonBossId,
                   int& lastBossKillDay);
