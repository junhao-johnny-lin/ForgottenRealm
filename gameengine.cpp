// FILE: src/GameEngine.cpp
#include "GameEngine.h"
#include "Dungeon_1_2.h"
#include "SaveSystem.h"
#include "Weapon.h"
#include "Armor.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "location_1_2.h"

using namespace Adventure;

GameEngine::GameEngine()
    : map_(), player_("Hero"), be_(), world_(), achievements_() {
    std::srand((unsigned)std::time(nullptr));
    // starter gear (class allowed lists)
    std::vector<ClassType> swordClasses = { ClassType::Knight, ClassType::Paladin, ClassType::Lancer };
    std::vector<ClassType> staffClasses = { ClassType::Mage, ClassType::Alchemist, ClassType::Summoner };
    player_.addItem(std::make_shared<Weapon>(1,"Starter Sword",6,40,ItemRarity::Common,swordClasses));
    player_.addItem(std::make_shared<Armor>(2,"Leather Armor",2,30,ItemRarity::Common,std::vector<ClassType>{ClassType::Ranger,ClassType::Scout}));
    player_.setClass(ClassType::Knight);
    player_.setLocationIndex(1); // Araluen default
}

void GameEngine::run() {
    bool running = true;
    while (running) {
        showMainMenu();
        int choice;
        if (!(std::cin >> choice)) { std::cin.clear(); std::cin.ignore(10000,'\n'); continue; }
        switch(choice) {
        case 1: map_.draw(); break;
        case 2: std::cout << player_.status() << "\n"; break;
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

void GameEngine::randomEncounter() {
    int r = std::rand()%100;
    if (r < 5) {
        Enemy boss("Random Plains Boss", 120, 15, 12, EnemyTier::Epic);
        boss.applyDayScaling(world_.day(), !world_.isBossCleared(1));
        be_.fight(player_, boss);
    } else {
        Enemy e("Wild Wolf", 12, 3, 1, EnemyTier::Normal);
        e.applyDayScaling(world_.day(), false);
        be_.fight(player_, e);
    }
}

void GameEngine::enterDungeon() {
    int idx = player_.locationIndex();
    if (idx < 0 || idx >= (int)map_.locations().size()) { std::cout << "Invalid location index\n"; return; }
    const Location& loc = map_.locations()[idx];
    if (!loc.hasDungeon()) { std::cout << "No dungeon here.\n"; return; }

    std::cout << "Entering dungeon at " << loc.id() << "\n";
    // every dungeon has 15 floors: per your choice (C)
    Enemy bossPrototype(loc.id() + " Ancient", 200 + idx*50, 20 + idx*5, 10 + idx, EnemyTier::Boss);
    Dungeon d(loc.id());
    d.build(15, bossPrototype, idx);

    // For each floor
    for (const auto& floor : d.floors()) {
        std::cout << "Floor " << floor.floorNumber << " - Enemies: " << floor.enemies.size() << "\n";
        for (auto en : floor.enemies) {
            // apply day scaling to each enemy using world day and whether previous boss uncleared (for ultimate rules only)
            bool prevUncleared = !world_.isBossCleared(idx);
            en.applyDayScaling(world_.day(), prevUncleared);
            bool win = be_.fight(player_, en);
            if (!win) { std::cout << "You retreated to an inn. Dungeon progress saved at floor " << floor.floorNumber << "\n"; return; }
        }
        if (floor.hasBoss) {
            std::cout << "Boss encountered on floor " << floor.floorNumber << "\n";
            // For Hibernia (index 0) make it ultimate multi-phase
            if (idx == 0) {
                Enemy ultimate = floor.enemies.front();
                // ultimate boss scaling: apply world scaling (special)
                ultimate.applyDayScaling(world_.day(), !world_.isBossCleared(idx));
                bool win = be_.fightMultiPhase(player_, ultimate, world_, idx);
                if (!win) { std::cout << "Defeated by ultimate boss.\n"; return; }
            } else {
                Enemy boss = floor.enemies.front();
                boss.applyDayScaling(world_.day(), false);
                bool win = be_.fight(player_, boss);
                if (!win) { std::cout << "Defeated by boss.\n"; return; }
                // mark boss cleared for area
                world_.setBossCleared(idx, true);
                // give reward & achievement
                giveDungeonRewardAndAchievement(idx);
            }
        }
    }
    std::cout << "Dungeon fully cleared!\n";
    world_.setDungeonCleared(idx, true);
    giveDungeonRewardAndAchievement(idx);
}

void GameEngine::visitTrainer() {
    int idx = player_.locationIndex();
    if (idx < 0 || idx >= (int)map_.locations().size()) { std::cout << "Invalid location index\n"; return; }
    Location* loc = map_.getLocationById(map_.locations()[idx].id());
    if (!loc || !loc->hasTrainer()) { std::cout << "No trainer here.\n"; return; }
    Trainer* t = loc->trainer();
    std::cout << "Trainer " << t->name() << " offers:\n";
    const auto& skills = t->skills();
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
    for (size_t i=0;i<locs.size();++i) std::cout << i << ": " << locs[i].id() << " - " << locs[i].desc() << "\n";
    std::cout << "Enter index to travel: ";
    int idx; if(!(std::cin >> idx)) { std::cin.clear(); std::cin.ignore(10000,'\n'); return; }
    if (idx >=0 && idx < (int)locs.size()) {
        player_.setLocationIndex(idx);
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
    SaveSystem::saveAll(player_, world_, "save1.dat");
}

void GameEngine::load() {
    SaveSystem::loadAll(player_, world_, "save1.dat");
}

void GameEngine::checkAndApplyAchievement(const std::string& aid) {
    if (!achievements_.isUnlocked(aid)) {
        achievements_.unlock(aid);
        const Achievement* a = achievements_.get(aid);
        if (a) {
            std::cout << "Achievement unlocked: " << a->name << "\n";
            player_.applyAchievementBonus(*a);
        }
    }
}

void GameEngine::giveDungeonRewardAndAchievement(int idx) {
    const auto& loc = map_.locations()[idx];
    // give sample reward: weapon or armor based on idx
    if (idx % 2 == 0) {
        player_.addItem(std::make_shared<Weapon>(100+idx, loc.id()+" Trophy Sword", 10 + idx/2, 50, ItemRarity::Rare));
        std::cout << "Found " << loc.id() << " Trophy Sword!\n";
    } else {
        player_.addItem(std::make_shared<Armor>(200+idx, loc.id()+" Trophy Armor", 5 + idx/2, 50, ItemRarity::Rare));
        std::cout << "Found " << loc.id() << " Trophy Armor!\n";
    }
    // achievement
    const auto& aids = loc.achievementIds();
    if (!aids.empty()) {
        checkAndApplyAchievement(aids.front());
    } else {
        // generic achievement
        checkAndApplyAchievement(loc.id() + "_clear");
    }
}

