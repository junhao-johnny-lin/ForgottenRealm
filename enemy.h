// enemy.h
#pragma once
#include <string>
#include <vector>

struct Enemy {
    std::string id;
    std::string name;
    int hp = 0;
    int attack = 0;
    int defence = 0;
    std::vector<std::string> itemDrops;
};

const std::vector<Enemy>& getDefaultEnemies();
