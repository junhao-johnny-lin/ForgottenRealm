#pragma once
#include <unordered_map>
#include <string>
#include "player.h"
#include "class_defs.h"

void openTrainer(PlayerState& player, const std::unordered_map<std::string, ClassDef>& classes);
