// FILE: include/BattleEngine.h
#pragma once
#include "Player_1_2.h"
#include "Enemy_1_2.h"

namespace Adventure {

class BattleEngine {
public:
    BattleEngine() = default;

    // returns true if player wins, false if player flees or dies
    bool fight(Player& p, Enemy& e);

    // optional: expose simple multi-phase fighting later
};

} // namespace Adventure
