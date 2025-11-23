// save.h
#pragma once
#include "items.h"
#include "loot.h"
#include "achievements.h"
#include <string>
#include <vector>

bool saveGame(const std::string& path,
              const std::vector<WeaponInstance>& weapons,
              const std::vector<Potion>& potions,
              const std::vector<Achievement>& achievements);

bool loadGame(const std::string& path,
              std::vector<WeaponInstance>& weapons,
              std::vector<Potion>& potions,
              std::vector<Achievement>& achievements);
