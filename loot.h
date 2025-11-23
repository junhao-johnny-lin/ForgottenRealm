#pragma once
#include <string>
#include <vector>
#include "player.h"
#include "enemy.h"

// Generate loot item ids for a given enemy
std::vector<std::string> generateLootForEnemy(const Enemy& enemy);

// Apply a named loot item effect to the player (perm or temporary)
void applyLootItemToPlayer(PlayerState& player, const std::string& itemId);
