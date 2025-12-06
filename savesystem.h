// FILE: savesystem.h
#pragma once
#include <string>

namespace Adventure {

class Player;
class GameWorld;

class SaveSystem {
public:
    static bool saveAll(const Player& p, const GameWorld& w, const std::string& path);
    static bool loadAll(Player& p, GameWorld& w, const std::string& path);
};

} // namespace Adventure
