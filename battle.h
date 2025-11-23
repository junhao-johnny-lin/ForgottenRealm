#pragma once
#include <vector>
#include <functional>
#include <cstdint>
#include "player.h"
#include "enemy.h"

enum class BattleOutcome { WIN, LOSE, FLEE };

struct BattleEvent { std::string text; };

struct BattleResult {
    BattleOutcome outcome = BattleOutcome::LOSE;
    int xpGained = 0;
    int reviveTokensGained = 0;
    std::vector<std::string> itemDrops;
    PlayerState finalPlayerState;
    std::vector<BattleEvent> events;
};

using BattleEventCallback = std::function<void(const BattleEvent&)>;

struct BattleContext {
    bool allowFlee = true;
    float xpMultiplier = 1.0f;
};

BattleResult runBattle(const PlayerState& player,
                       const std::vector<Enemy>& enemies,
                       const BattleContext& ctx = {},
                       uint32_t seed = 0,
                       BattleEventCallback cb = nullptr);
