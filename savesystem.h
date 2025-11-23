// FILE: include/SaveSystem.h
#pragma once
#include "Player_1_2.h"
#include "GameWorld.h"
#include <string>

namespace Adventure {

class SaveSystem {
public:
    static bool saveAll(const Player& p, const GameWorld& world, const std::string& filename);
    static bool loadAll(Player& p, GameWorld& world, const std::string& filename);
};

} // namespace Adventure
