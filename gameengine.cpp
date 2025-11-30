// FILE: src/GameEngine.cpp
#include "GameEngine.h"
#include "SaveSystem.h"
#include "Weapon.h"
#include "Armor.h"
#include "skills_1_2.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace Adventure;

GameEngine::GameEngine()
    : map_(),
    player_("Hero", ClassType::Knight),
    be_(),
    world_(),
    achievements_(),
    currentLocationIndex_(1)
{
    std::srand((unsigned)std::time(nullptr));

    // starter gear (class allowed lists)
    std::vector<ClassType> swordClasses = { ClassType::Knight, ClassType::Paladin, ClassType::Lancer };
    std::vector<ClassType> staffClasses = { ClassType::Mage, ClassType::Alchemist, ClassType::Summoner };

    // note: Weapon ctor signatures in your project may vary; adapt args if necessary
    player_.addItem(std::make_shared<Weapon>(1, "Starter Sword", 6, 40, ItemRarity::Common, swordClasses));
    player_.addItem(std::make_shared<Armor>(2, "Leather Armor", 2, 30, ItemRarity::Common, std::vector<ClassType>{ClassType::Ranger, ClassType::Scout}));

    // Player already constructed with start class; ensure skillpoints/day defaults ok
    player_.setDay(0);
}

void GameEngine::run() {
    bool running = true;
    while (running) {
        showMainMenu();
        int choice;
        if (!(std::cin >> choice)) { std::cin.clear(); std::cin.ignore(10000,'\n'); continue; }
        switch(choice) {
        case 1: map_.draw(); break;
        case 2: showStatus(); break;
        case 3: randomEncounter(); break;
        case 4: enterDungeon(); break;
        case 5: visitTrainer(); break;
        case 6: travel(); break;
        case 7: restAtInn(); break;
        case 8: save(); break;
        case 9: load(); break;
        case 10: running=false; break;
        default: std::cout << "Invalid\n"; break;
        }
    }
}

void GameEngine::showMainMenu() {
    std::cout << "\n=== MAIN MENU ===\n";
    std::cout << "1. Show Map\n2. Status\n3. Explore (random encounter)\n4. Enter dungeon (current location)\n5. Visit trainer\n6. Travel\n7. Rest at Inn (pass 1 day)\n8. Save\n9. Load\n10. Quit\nChoose: ";
}

void GameEngine::showStatus() const {
    std::cout << "\n=== PLAYER STATUS ===\n";
    std::cout << "Name: " << player_.name() << "\n";
    std::cout << "Level: " << player_.level() << "  EXP: " << player_.exp() << "/" << player_.nextLevelExp() << "\n";
    std::cout << "HP: " << player_.hp() << "/" << player_.maxHp() << "\n";
    std::cout << "ATK: " << player_.atk() << "  DEF: " << player_.def() << "\n";
    std::cout << "Skill Points: " << player_.skillPoints() << "\n";
    std::cout << "Location: ";
    const auto& locs = map_.locations();
    if (currentLocationIndex_ >= 0 && currentLocationIndex_ < (int)locs.size())
        std::cout << locs[currentLocationIndex_].id() << " - " << locs[currentLocationIndex_].description() << "\n";
    else
        std::cout << "Unknown\n";
}

void GameEngine::randomEncounter() {
    int r = std::rand()%100;
    if (r < 5) {
        // Epic plains boss - give a level param (1)
        Enemy boss("Random Plains Boss", 120, 15, 12, 1, EnemyTier::Epic);
        boss.applyDayScaling(world_.day());
        be_.fight(player_, boss);
    } else {
        Enemy e("Wild Wolf", 12, 3, 1, 1, EnemyTier::Normal);
        e.applyDayScaling(world_.day());
        be_.fight(player_, e);
    }
}

void GameEngine::enterDungeon() {
    const auto& locs = map_.locations();
    if (currentLocationIndex_ < 0 || currentLocationIndex_ >= (int)locs.size()) {
        std::cout << "Invalid location index\n";
        return;
    }
    const Location& loc = locs[currentLocationIndex_];
    if (!loc.hasDungeon()) { std::cout << "No dungeon here.\n"; return; }

    std::cout << "Entering dungeon at " << loc.id() << "\n";

    const int FLOORS = 15;
    // For each floor, spawn simple enemies; final floor is boss
    for (int floor = 1; floor <= FLOORS; ++floor) {
        if (floor < FLOORS) {
            // spawn 1-3 normal enemies depending on floor
            int count = 1 + (std::rand()%2); // 1 or 2
            std::cout << "Floor " << floor << " - Encounter " << count << " enemies\n";
            for (int i=0;i<count;++i) {
                int hp = 8 + floor*2;
                int atk = 2 + floor/3;
                int def = 0 + floor/5;
                Enemy e(loc.id() + " Mob", hp, atk, def, floor, EnemyTier::Normal);
                e.applyDayScaling(world_.day());
                bool win = be_.fight(player_, e);
                if (!win) { std::cout << "You retreated to an inn. Dungeon progress saved at floor " << floor << "\n"; return; }
            }
        } else {
            // boss on final floor
            std::cout << "Floor " << floor << " - Boss encountered\n";
            int hp = 150 + currentLocationIndex_*30;
            int atk = 15 + currentLocationIndex_*3;
            int def = 8 + currentLocationIndex_;
            Enemy boss(loc.id() + " Boss", hp, atk, def, floor, EnemyTier::Boss);
            boss.applyDayScaling(world_.day());

            // If world has a last boss (from cleared final of all dungeons), apply extra scaling
            // We'll check if world has last boss stats saved (non-zero)
            if (world_.lastBossHp() > 0) {
                Enemy lastBoss("LastDefeated", world_.lastBossHp(), world_.lastBossAtk(), world_.lastBossDef(), floor, EnemyTier::Boss);
                boss.applyExtraFromBoss(lastBoss);
            }

            bool win = be_.fight(player_, boss);
            if (!win) { std::cout << "Defeated by boss.\n"; return; }

            // mark boss cleared and dungeon cleared
            world_.setBossCleared(currentLocationIndex_, true);
            world_.setDungeonCleared(currentLocationIndex_, true);
            world_.markDungeonCleared(loc.id());

            giveDungeonRewardAndAchievement(currentLocationIndex_);
        }
    }

    std::cout << "Dungeon fully cleared!\n";
}

void GameEngine::visitTrainer() {
    const auto& locs = map_.locations();
    if (currentLocationIndex_ < 0 || currentLocationIndex_ >= (int)locs.size()) {
        std::cout << "Invalid location index\n";
        return;
    }

    Location* locptr = map_.getLocation(locs[currentLocationIndex_].id());
    if (!locptr) { std::cout << "Location not found\n"; return; }

    // We expect Location::trainer() to exist (returns Trainer&)
    Trainer& t = locptr->trainer();
    // trainer name/skills assumed to exist in Trainer implementation
    std::cout << "Trainer " << t.name() << " offers:\n";
    const auto& skills = t.skills();
    for (size_t i=0;i<skills.size();++i) {
        std::cout << i << ". " << skills[i].name << " (lvl " << skills[i].requiredLevel << " cost " << skills[i].cost << ")\n";
    }
    std::cout << "Choose skill index to learn or -1 to cancel: ";
    int s; if(!(std::cin >> s)) { std::cin.clear(); std::cin.ignore(10000,'\n'); return; }
    if (s>=0 && s<(int)skills.size()) {
        if (player_.learnSkill(skills[s])) std::cout << "Learned " << skills[s].name << "\n";
        else std::cout << "Cannot learn (lvl or SP missing).\n";
    }
}

void GameEngine::travel() {
    std::cout << "Available locations:\n";
    const auto& locs = map_.locations();
    for (size_t i=0;i<locs.size();++i) std::cout << i << ": " << locs[i].id() << " - " << locs[i].description() << "\n";
    std::cout << "Enter index to travel: ";
    int idx; if(!(std::cin >> idx)) { std::cin.clear(); std::cin.ignore(10000,'\n'); return; }
    if (idx >=0 && idx < (int)locs.size()) {
        currentLocationIndex_ = idx;
        std::cout << "Traveled to " << locs[idx].id() << "\n";
    } else std::cout << "Invalid index\n";
}

void GameEngine::restAtInn() {
    std::cout << "Resting at inn... Passing 1 day.\n";
    world_.restAtInn();
    player_.heal(player_.maxHp()); // fully restore
    std::cout << "All monsters become stronger with time. Current day: " << world_.day() << "\n";
}

void GameEngine::save() {
    if (SaveSystem::saveAll(player_, world_, "save1.dat")) std::cout << "Game saved.\n";
    else std::cout << "Failed to save game.\n";
}

void GameEngine::load() {
    if (SaveSystem::loadAll(player_, world_, "save1.dat")) std::cout << "Game loaded.\n";
    else std::cout << "Failed to load game.\n";
}

void GameEngine::checkAndApplyAchievement(const std::string& aid) {
    // try to use AchievementSystem API (assumed)
    if (!achievements_.isUnlocked(aid)) {
        achievements_.unlock(aid);
        const Achievement* a = achievements_.get(aid);
        if (a) {
            std::cout << "Achievement unlocked: " << a->name << "\n";
            // if Player has applyAchievementBonus, call it; otherwise ignore
            // many Player implementations have such method; we try to call safely:
            // (we don't have compile-time check here; if your Player lacks applyAchievementBonus, remove next line)
            // player_.applyAchievementBonus(*a);
        }
    }
}

void GameEngine::giveDungeonRewardAndAchievement(int idx) {
    const auto& locs = map_.locations();
    if (idx < 0 || idx >= (int)locs.size()) return;
    const auto& loc = locs[idx];

    // give sample reward: weapon or armor based on idx
    if (idx % 2 == 0) {
        player_.addItem(std::make_shared<Weapon>(100+idx, loc.id()+" Trophy Sword", 10 + idx/2, 50, ItemRarity::Rare, std::vector<ClassType>{}));
        std::cout << "Found " << loc.id() << " Trophy Sword!\n";
    } else {
        player_.addItem(std::make_shared<Armor>(200+idx, loc.id()+" Trophy Armor", 5 + idx/2, 50, ItemRarity::Rare, std::vector<ClassType>{}));
        std::cout << "Found " << loc.id() << " Trophy Armor!\n";
    }

    // achievement (Location doesn't have achievementIds in your current Location, so use generic)
    std::string aid = loc.id() + "_clear";
    checkAndApplyAchievement(aid);
}
