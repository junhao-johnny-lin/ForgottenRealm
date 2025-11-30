// FILE: include/SaveSystem.h
#pragma once
#include <string>

namespace Adventure {
class Player;
class GameWorld;

class SaveSystem {
public:
    // path can be any relative path; we used /mnt/data/Document.pdf as reference in docs.
    static bool saveAll(const Player& p, const GameWorld& w, const std::string& path);
    static bool loadAll(Player& p, GameWorld& w, const std::string& path);
};

} // namespace Adventure
