// game.cpp
#include "game.h"
#include "achievements.h"
#include "enemy.h"
#include "items.h"
#include "loot.h"
#include "player.h"
#include <iostream>
#include <memory>
#include <vector>

struct Game::Impl {
    std::vector<Enemy> enemies;
    std::vector<std::string> achievementIds;
    Impl() {
        enemies = getDefaultEnemies();
        auto ach = getDefaultAchievements();
        for (const auto& a : ach) achievementIds.push_back(a.id);
    }
};

Game::Game() : pimpl_(new Impl{}) {}
Game::~Game() { delete pimpl_; }

void Game::initDefault() {
    pimpl_->enemies = getDefaultEnemies();
}

void Game::run() {
    std::cout << "Game starting (simple loop)\n";
    // minimal loop stub
    for (int i = 0; i < 1; ++i) {
        std::cout << "Tick\n";
    }
}

const std::vector<Enemy>& Game::enemies() const { return pimpl_->enemies; }
const std::vector<std::string>& Game::achievements() const { return pimpl_->achievementIds; }
