// game.h
#pragma once
#include <string>
#include <vector>

struct Achievement;
struct Enemy;
struct Mob;
struct Potion;
class PlayerState;
class Weapon;

class Game {
public:
    Game();
    ~Game();

    void initDefault();
    void run(); // main loop

    // accessors
    const std::vector<Enemy>& enemies() const;
    const std::vector<std::string>& achievements() const;

private:
    struct Impl;
    Impl* pimpl_;
};
