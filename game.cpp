#include "game.h"
#include "battle.h"
#include "save.h"
#include "class_skills.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Game::Game() {
    tpl_ = getTemplateLines();
    nodes_ = getDefaultNodesCopy();
    nodes_["south_cliffs"].current = true;
    achievements_ = getDefaultAchievements();
    player_.currentLocationKey = "south_cliffs";
    // init: last boss baseline
    lastNewDungeonBossId_ = "boss_generic";
    lastBossKillDay_ = 0;

    std::cout << "Welkom. Type 'help' voor commands.\n";
}

void Game::runLoop() {
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;
        if (line == "quit" || line == "exit") break;
        if (line == "help") {
            std::cout << "Commands:\n"
                         "  map | map full\n"
                         "  where | look\n"
                         "  inn                    (dag +1)\n"
                         "  fight <enemyId>\n"
                         "  boss                   (scaled dungeon boss)\n"
                         "  ultimate               (Hibernia ultimate boss)\n"
                         "  classskills            (toon class skills)\n"
                         "  buyclass <skillId>     (koop class skill)\n"
                         "  save [path] | load [path]\n"
                         "  quit\n";
            continue;
        }
        handleCommand(line);
    }
}

void Game::handleCommand(const std::string& cmd) {
    std::istringstream iss(cmd);
    std::string t; iss >> t;
    if (t == "map") { std::string arg; if (iss >> arg && arg=="full") cmdMap(true); else cmdMap(false); return; }
    if (t == "where") { cmdWhere(); return; }
    if (t == "look") { cmdLook(); return; }
    if (t == "inn") { cmdInn(); return; }
    if (t == "fight") { std::string id; if (iss >> id) cmdFight(id); else std::cout << "fight <enemyId>\n"; return; }
    if (t == "boss") { cmdBossFight(); return; }
    if (t == "ultimate") { cmdUltimate(); return; }
    if (t == "classskills") { cmdSkillsList(); return; }
    if (t == "buyclass") { std::string id; if (iss >> id) cmdBuyClassSkill(id); else std::cout << "buyclass <id>\n"; return; }
    if (t == "save") { std::string p="savegame.dat"; if (iss >> p) cmdSave(p); else cmdSave(p); return; }
    if (t == "load") { std::string p="savegame.dat"; if (iss >> p) cmdLoad(p); else cmdLoad(p); return; }
    std::cout << "Unknown command. Type 'help'.\n";
}

void Game::cmdMap(bool full) {
    printFullMapWithMarkersColored(nodes_, tpl_, full);
}

void Game::cmdWhere() const {
    std::cout << "Dag: " << player_.dayCount
              << " | Locatie: " << player_.currentLocationKey
              << " | Level: " << player_.level
              << " | SP: " << player_.skillPoints
              << " | HP: " << player_.hp << "/" << player_.maxHp << "\n";
}

void Game::cmdLook() const {
    auto it = nodes_.find(player_.currentLocationKey);
    if (it == nodes_.end()) { std::cout << "Geen info.\n"; return; }
    const auto& L = it->second;
    std::cout << L.label << " — " << L.description << " | Enemies nearby: " << L.enemiesNearby << "\n";
}

void Game::cmdInn() {
    player_.dayCount += 1;
    player_.hp = player_.maxHp;
    std::cout << "Je rust in de inn. Dag is nu " << player_.dayCount << ". HP hersteld.\n";
}

void Game::cmdFight(const std::string& enemyId) {
    const auto& types = getEnemyTypes();
    auto it = types.find(enemyId);
    if (it == types.end()) { std::cout << "Enemy onbekend.\n"; return; }
    EnemyType e = it->second;
    // groei voor niet-boss enemies
    if (e.tier != EnemyTier::Boss && e.tier != EnemyTier::UltimateBoss) {
        e.baseHp = scaleDailyStat(e.baseHp, e.growthFactor, player_.dayCount);
        e.baseAttack = scaleDailyStat(e.baseAttack, e.growthFactor, player_.dayCount);
        e.baseDefence = scaleDailyStat(e.baseDefence, e.growthFactor, player_.dayCount);
        e.baseXP = scaleDailyXP(e.baseXP, e.growthFactor*2.0, player_.dayCount);
    }
    auto res = fight(player_, e);
    if (res.playerWon) gainXP(player_, res.xpEarned);
}

void Game::cmdBossFight() {
    const auto& types = getEnemyTypes();
    auto it = types.find("boss_generic");
    if (it == types.end()) { std::cout << "Boss type ontbreekt.\n"; return; }
    // Boss groeit: +10% stats/dag, +20% XP/dag
    EnemyType scaled = makeScaledDungeonBoss(it->second, player_.dayCount);
    auto res = fight(player_, scaled);
    if (res.playerWon) {
        gainXP(player_, res.xpEarned);
        // update laatste NIEUWE dungeon boss referentie (geen reruns)
        // In een echte dungeon-setup zou je unieke ids hebben per dungeon boss.
        // Hier updaten we alleen als het een andere boss-id is dan de huidige referentie.
        if (lastNewDungeonBossId_ != scaled.id) {
            lastNewDungeonBossId_ = scaled.id;
            lastBossKillDay_ = player_.dayCount;
        }
    }
}

void Game::cmdUltimate() {
    if (player_.currentLocationKey != "hibernia") {
        std::cout << "Ultimate Boss verschijnt alleen in Hibernia.\n"; return;
    }
    const auto& types = getEnemyTypes();
    auto it = types.find(lastNewDungeonBossId_);
    if (it == types.end()) { std::cout << "Referentieboss ontbreekt.\n"; return; }
    int daysSince = std::max(0, player_.dayCount - lastBossKillDay_);
    BossStats ub = generateUltimateBoss(it->second, daysSince);
    EnemyType eUB;
    eUB.id = "ultimate_hibernia";
    eUB.name = "Ultimate Boss of Hibernia";
    eUB.tier = EnemyTier::UltimateBoss;
    eUB.baseHp = ub.hp; eUB.baseAttack = ub.attack; eUB.baseDefence = ub.defence; eUB.baseXP = ub.xp;
    eUB.isBoss = true; eUB.growthFactor = 0.0;

    auto res = fight(player_, eUB);
    if (res.playerWon) gainXP(player_, res.xpEarned);
}

void Game::cmdSkillsList() const {
    const auto& cls = getClassSkills();
    auto it = cls.find(player_.classId);
    if (it == cls.end()) { std::cout << "Geen skills voor class.\n"; return; }
    std::cout << "Class: " << player_.classId << " — beschikbare skills:\n";
    for (const auto& s : it->second) {
        bool has = std::find(player_.unlockedClassSkills.begin(), player_.unlockedClassSkills.end(), s.id) != player_.unlockedClassSkills.end();
        std::cout << (has ? "[x] " : "[ ] ") << s.id << " (" << s.cost << " SP) — " << s.name << ": " << s.description << "\n";
    }
}

void Game::cmdBuyClassSkill(const std::string& id) {
    buyClassSkill(player_, id);
}

void Game::cmdSave(const std::string& path) const {
    if (saveGameState(path, nodes_, achievements_, player_, lastNewDungeonBossId_, lastBossKillDay_))
        std::cout << "Saved: " << path << "\n";
    else std::cout << "Save mislukt.\n";
}

void Game::cmdLoad(const std::string& path) {
    if (loadGameState(path, nodes_, achievements_, player_, lastNewDungeonBossId_, lastBossKillDay_))
        std::cout << "Loaded: " << path << "\n";
    else std::cout << "Load mislukt.\n";
}
