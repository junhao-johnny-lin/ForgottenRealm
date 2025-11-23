#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "player.h"
#include "map_renderer.h"
#include "achievements.h"

bool saveGame(const PlayerState& player,
              const std::unordered_map<std::string, Location>& nodes,
              const std::vector<Achievement>& achievements,
              const std::string& path);

bool loadGame(PlayerState& player,
              std::unordered_map<std::string, Location>& nodes,
              std::vector<Achievement>& achievements,
              const std::string& path);
