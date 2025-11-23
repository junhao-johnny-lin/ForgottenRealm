#include "battle.h"
#include <random>
#include <algorithm>
#include <sstream>
#include "trainer.h"


static inline int resolveDamage(int atk, int def, std::mt19937& rng) {
    std::uniform_int_distribution<int> var(0,2);
    int variance = var(rng);
    int dmg = atk - (def / 2) + variance;
    return std::max(1, dmg);
}

static inline void pushEvent(BattleResult& res, const std::string& txt, BattleEventCallback cb) {
    BattleEvent ev{txt};
    res.events.push_back(ev);
    if (cb) cb(ev);
}

BattleResult runBattle(const PlayerState& player,
                       const std::vector<Enemy>& enemiesIn,
                       const BattleContext& ctx,
                       uint32_t seed,
                       BattleEventCallback cb)
{
    BattleResult res;
    PlayerState p = player;
    res.finalPlayerState = p;

    std::mt19937 rng;
    if (seed == 0) {
        std::random_device rd;
        rng.seed(rd());
    } else {
        rng.seed(seed);
    }

    struct Mob { std::string id; std::string name; int hp; int atk; int def; bool alive; };
    std::vector<Mob> mobs;
    mobs.reserve(enemiesIn.size());
    for (const auto &e : enemiesIn) {
        mobs.push_back(Mob{e.id, e.name, e.hp, e.attack, e.defense, e.hp > 0});
    }

    if (mobs.empty()) {
        pushEvent(res, "Geen vijanden — automatische winst.", cb);
        res.outcome = BattleOutcome::WIN;
        res.finalPlayerState = p;
        return res;
    }

    pushEvent(res, "Battle start!", cb);
    const int fleeChance = 40;

    while (p.hp > 0) {
        if (ctx.allowFlee && p.hp <= std::max(1, p.maxHp / 5)) {
            std::uniform_int_distribution<int> dist(1, 100);
            int roll = dist(rng);
            std::ostringstream ss; ss << "Probeert te vluchten (roll " << roll << ")";
            pushEvent(res, ss.str(), cb);
            if (roll <= fleeChance) {
                pushEvent(res, "Vlucht geslaagd.", cb);
                res.outcome = BattleOutcome::FLEE;
                res.finalPlayerState = p;
                return res;
            }
            pushEvent(res, "Vlucht mislukt.", cb);
        }

        /// choose weakest alive mob
        auto it = std::min_element(mobs.begin(), mobs.end(), [](const Mob& a, const Mob& b) {
            if (!a.alive) return false;
            if (!b.alive) return true;
            return a.hp < b.hp;
        });

        // if selection failed or points to a dead mob, pick first alive using find_if
        if (it == mobs.end() || !it->alive) {
            auto itAlive = std::find_if(mobs.begin(), mobs.end(), [](const Mob& m){ return m.alive; });
            if (itAlive == mobs.end()) break; // no alive mobs -> exit battle loop
            it = itAlive;
        }


        // player turn
        {
            int baseAtk = p.attack + p.permAttackBoost + p.tempAttackBoost;
            int dmg = resolveDamage(baseAtk, it->def, rng);
            it->hp -= dmg;
            if (it->hp <= 0) it->alive = false;
            std::ostringstream ss; ss << "Player hits " << it->name << " for " << dmg;
            pushEvent(res, ss.str(), cb);
        }

        // check victory
        bool anyAlive = false;
        for (const auto &m : mobs) if (m.alive) { anyAlive = true; break; }
        if (!anyAlive) {
            pushEvent(res, "Alle vijanden verslagen.", cb);
            res.outcome = BattleOutcome::WIN;
            int xp = 0;
            for (const auto &m : mobs) xp += (m.atk + m.def + std::max(1, m.hp)) * 2;
            xp = static_cast<int>(xp * ctx.xpMultiplier);
            res.xpGained = xp;
            p.xp += xp;
            if ((rng() % 100) < 5) { res.reviveTokensGained = 1; p.reviveTokens += 1; }
            res.finalPlayerState = p;
            return res;
        }

        // mobs' turn
        for (auto &m : mobs) {
            if (!m.alive) continue;
            int dmgm = resolveDamage(m.atk, p.defence + p.permDefenceBoost + p.tempDefenceBoost, rng);
            p.hp -= dmgm;
            std::ostringstream s2; s2 << m.name << " hits Player for " << dmgm;
            pushEvent(res, s2.str(), cb);
            if (p.hp <= 0) break;
        }

        if (p.hp <= 0) break;
    }

    if (p.hp <= 0) {
        pushEvent(res, "Je bent verslagen.", cb);
        res.outcome = BattleOutcome::LOSE;
        int lost = std::min(p.xp, 10);
        p.xp -= lost;
        res.finalPlayerState = p;
        return res;
    }

    res.finalPlayerState = p;
    return res;
}
