// FILE: include/BattleEngine.h
#pragma once
#include "Player_1_2.h"
#include "gameworld.h"
#include "Enemy_1_2.h"
#include <iostream>

namespace Adventure {

class BattleEngine {
public:
    BattleEngine();
    bool fight(Player& p, Enemy& e); // single-enemy fight
    bool fightMultiPhase(Player& p, Enemy bossPrototype, GameWorld& world, int dungeonIdx); // for Hibernia/ultimate
};

} // namespace Adventure
