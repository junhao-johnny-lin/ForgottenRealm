#pragma once
#include <string>

// Minimal Enemy definition used by battle, loot and other systems.
// Extend fields as needed to match your game's enemy.h if it already exists.
struct Enemy {
    std::string id;
    std::string name;
    int hp = 10;
    int attack = 3;
    int defense = 1;
    int category = 0; // optional: use int categories for loot/logic, 0 = default
};
