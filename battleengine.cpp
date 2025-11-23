// FILE: src/BattleEngine.cpp
#include "BattleEngine.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std::chrono_literals;

namespace Adventure {

BattleEngine::BattleEngine() { std::srand((unsigned)std::time(nullptr)); }

static int randRange(int a,int b){ return a + (std::rand() % (b-a+1)); }

bool BattleEngine::fight(Player& p, Enemy& e) {
    std::cout << "Fight: " << p.name() << " vs " << e.name() << " (Lv " << e.level() << ")\n";
    // very simple speed: higher level acts first sometimes
    while (p.hp() > 0 && e.hp() > 0) {
        bool playerTurn = randRange(0,1) == 1;
        if (playerTurn) {
            int dmg = p.equippedWeaponDamage();
            std::cout << p.name() << " attacks for " << dmg << "\n";
            e.takeDamage(dmg);
        } else {
            int dmg = e.atk();
            std::cout << e.name() << " attacks for " << dmg << "\n";
            p.takeDamage(dmg);
        }
        std::this_thread::sleep_for(120ms);
    }
    bool win = e.isDead() && p.hp() > 0;
    if (win) {
        int baseExp = 20 + e.level() * 10;
        std::cout << "Victory! Gained " << baseExp << " EXP.\n";
        p.gainExp(baseExp);
    } else {
        std::cout << "You were defeated...\n";
    }
    return win;
}

bool BattleEngine::fightMultiPhase(Player& p, Enemy bossPrototype, GameWorld& world, int dungeonIdx) {
    std::cout << "BEGIN MULTI-PHASE BOSS: " << bossPrototype.name() << "\n";
    // 3 phases: 100%, 50% summon, 25% enrage
    struct Phase { double hpScale; double atkScale; std::string desc; };
    std::vector<Phase> phases = {
        {1.0,1.0,"Phase 1: Calm"},
        {1.5,1.5,"Phase 2: Summon"},
        {2.0,2.5,"Phase 3: Enraged"}
    };

    for (size_t i=0;i<phases.size();++i) {
        const Phase& ph = phases[i];
        Enemy phaseBoss(bossPrototype.name() + " [" + std::to_string(i+1) + "]",
                        static_cast<int>(std::ceil(bossPrototype.hp() * ph.hpScale)),
                        static_cast<int>(std::ceil(bossPrototype.atk() * ph.atkScale)),
                        bossPrototype.level(),
                        EnemyTier::UltimateBoss);
        // apply day scaling with the rule for ultimate boss (GameWorld will note if previous boss uncleared)
        bool prevUncleared = !world.isBossCleared(dungeonIdx);
        phaseBoss.applyDayScaling(world.day(), prevUncleared);

        std::cout << ph.desc << " - Boss HP: " << phaseBoss.hp() << " ATK: " << phaseBoss.atk() << "\n";
        bool win = fight(p, phaseBoss);
        if (!win) {
            std::cout << "You were defeated in " << ph.desc << "\n";
            return false;
        } else {
            std::cout << "Phase " << (i+1) << " cleared!\n";
            p.heal( std::min( p.maxHp()/3, 30 ) ); // partial heal between phases
        }
    }
    p.gainExp(1000);
    std::cout << "You defeated the multi-phase ultimate boss!\n";
    world.setBossCleared(dungeonIdx, true);
    return true;
}

} // namespace Adventure
