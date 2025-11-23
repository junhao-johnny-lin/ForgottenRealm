#include "game.h"
#include "class_defs.h"
#include "save.h"
#include "battle.h"
#include "achievements.h"
#include <iostream>
#include <sstream>
#include <random>
#include <algorithm>
#include "trainer.h"

// trim helper — voeg dit toe direct onder de #include regels in game.cpp
static inline std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}


// Helper trim
// Normaliseer user input en keys: lowercase, underscores->spaces, verwijder punctuatie, collapse spaces
static inline std::string normalizeKey(std::string s) {
    for (auto &c : s) c = static_cast<char>(std::tolower((unsigned char)c));
    for (auto &c : s) if (c == '_') c = ' ';
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        if (std::isalnum((unsigned char)c) || c == ' ') out.push_back(c);
    }
    // collapse spaces
    std::string collapsed;
    bool lastSpace = false;
    for (char c : out) {
        if (c == ' ') {
            if (!lastSpace) { collapsed.push_back(c); lastSpace = true; }
        } else {
            collapsed.push_back(c); lastSpace = false;
        }
    }
    // trim
    size_t start = collapsed.find_first_not_of(' ');
    if (start == std::string::npos) return "";
    size_t end = collapsed.find_last_not_of(' ');
    return collapsed.substr(start, end - start + 1);
}

// Bouw de genormaliseerde lookup: normalized -> canonical key
template<typename LocMap>
static inline void buildNormalizedLookup(const LocMap& locations,
                                         std::unordered_map<std::string, std::string>& outLookup)
{
    outLookup.clear();
    for (const auto &kv : locations) {
        const std::string &origKey = kv.first;
        const std::string &label = kv.second.label;
        std::string n1 = normalizeKey(origKey);
        std::string n2 = normalizeKey(label);
        if (!n1.empty()) outLookup.emplace(n1, origKey);
        if (!n2.empty() && outLookup.find(n2) == outLookup.end()) outLookup.emplace(n2, origKey);
        // also add key variants: remove parentheses, common suffixes, etc.
        // quick variant: replace '(' and ')' from origKey and normalize again
        std::string stripped = origKey;
        for (char &c : stripped) if (c == '(' || c == ')' || c == ',' || c == ';') c = ' ';
        std::string n3 = normalizeKey(stripped);
        if (!n3.empty() && outLookup.find(n3) == outLookup.end()) outLookup.emplace(n3, origKey);
    }
}

Game::Game() {
    // default player fields
    player_.classId = "warrior";
    player_.level = 1;
    player_.xp = 0;
    player_.skillPoints = 0;
    player_.currentLocationKey = "araluen";
    player_.reviveTokens = 0;
    player_.permAttackBoost = 0;
    player_.permDefenceBoost = 0;
    player_.permHpBoost = 0;

    // default achievements (will be applied in initWorld)
    achievements_ = getDefaultAchievements();
}

void Game::initWorld() {
    nodes_.clear();
    dungeons_.clear();

                                // visited, accessible, has trainer, has camp, has dunguen, has inn, dungeon cleared
    // Picta sublocatie
    nodes_.emplace("Drowned_Forest", Location{"Drowned Forest", false, true, false, false, false, false, false});

    // Hibernia
    nodes_.emplace("Hibernia", Location{"HIBERNIA", false, true, false, false, false, false, false});

    // Araluen blok
    nodes_.emplace("Norgate", Location{"Norgate", false, true, false, false, false, false, false});
    nodes_.emplace("Forest(Araluen)", Location{"Forest(Araluen)", false, true, false, false, false, false, false});
    nodes_.emplace("forest araluen", Location{"Forest(Araluen)", false, true, false, false, false, false, false});
    nodes_.emplace("Araluen", Location{"Araluen", false, true, true, true, true, true, false}); // hasTrainer, hasCamp, hasDungeon, hasInn = true
    nodes_.emplace("3 Step Pass (Araluen)", Location{"3 Step Pass (Araluen)", false, true, false, false, false, false, false});
    nodes_.emplace("Hackham", Location{"Hackham", false, true, false, false, false, false, false});
    nodes_.emplace("Redmont", Location{"Redmont", false, true, false, false, false, false, false});
    nodes_.emplace("Gorlan", Location{"Gorlan", false, true, false, false, false, false, false});
    nodes_.emplace("Caraway", Location{"Caraway", false, true, false, false, false, false, false});
    nodes_.emplace("Thomtree", Location{"Thomtree", false, true, false, false, false, false, false});
    nodes_.emplace("Seacliff", Location{"Seacliff", false, true, false, false, false, false, false});
    nodes_.emplace("Western_World", Location{"Western_World", false, true, false, false, false, false, false});
    nodes_.emplace("Mountains", Location{"Mountains", false, true, false, false, false, false, false});
    nodes_.emplace("Uthal_Plain", Location{"Uthal_Plain", false, true, false, false, false, false, false});
    nodes_.emplace("The_Fens", Location{"The_Fens", false, true, false, false, false, false, false});
    nodes_.emplace("Solitary Plain", Location{"Solitary Plain", false, true, false, false, false, false, false});

    // Celtica sublocaties
    nodes_.emplace("Villages", Location{"Villages", false, true, false, false, false, false, false});
    nodes_.emplace("3 Step Pass (Celtica)", Location{"3 Step Pass (Celtica)", false, true, false, false, false, false, false});

    // Morgarath's Plateau sublocaties
    nodes_.emplace("3 Step Pass (Plateau)", Location{"3 Step Pass (Plateau)", false, true, false, false, false, false, false});
    nodes_.emplace("Mountains (Plateau)", Location{"Mountains (Plateau)", false, true, false, false, false, false, false});
    nodes_.emplace("South Cliffs", Location{"South Cliffs", false, true, false, false, false, false, false});


    // auto create dungeons per location
    for (const auto& kv : nodes_) {
        std::string id = "d_" + kv.first;
        dungeons_.emplace(id, makeDungeon(id, kv.second.label + " Depths", kv.first, 3));
    }

    // Ensure player location valid
    if (nodes_.find(player_.currentLocationKey) == nodes_.end()) player_.currentLocationKey = "araluen";

    // Ensure achievements exist and apply their permanent mods
    if (achievements_.empty()) achievements_ = getDefaultAchievements();
    applyAchievementsToPlayer(player_, achievements_);
}

void Game::runIntro() {
    // Rebuild normalized lookup after map is initialized (map.locations moet bestaan)
    buildNormalizedLookup(map.locations, canonicalKeyByNormalized);

    std::cout << "Welkom! Kies een startlocatie (bv. araluen, redmont, gorlan, fens, celtica, mountains) of ENTER om default te gebruiken:\n> ";
    std::string locInput;
    if (!std::getline(std::cin, locInput)) return;
    std::string nloc = normalizeKey(locInput);

    if (nloc.empty()) {
        std::cout << "Geen invoer; start op " << player_.currentLocationKey << ".\n";
        return;
    }

    auto it = canonicalKeyByNormalized.find(nloc);
    if (it != canonicalKeyByNormalized.end()) {
        const std::string chosenKey = it->second;
        auto nodeIt = map.locations.find(chosenKey);
        if (nodeIt != map.locations.end()) {
            player_.currentLocationKey = chosenKey;
            std::cout << "Startlocatie: " << nodeIt->second.label << " (" << chosenKey << ")\n";
            return;
        }
    }

    // geen exacte normalized match — probeer substring matches over normalized keys
    bool matched = false;
    for (const auto &kv : canonicalKeyByNormalized) {
        if (kv.first.find(nloc) != std::string::npos) {
            player_.currentLocationKey = kv.second;
            std::cout << "Gevonden vergelijkbare locatie: " << map.locations.at(kv.second).label
                      << " (" << kv.second << ") gebruikt.\n";
            matched = true;
            break;
        }
    }
    if (matched) return;

    // fallback: toon beschikbare opties en behoud default
    std::cout << "Locatie onbekend of niet toegankelijk. Start op " << player_.currentLocationKey << ".\n";
    std::cout << "Beschikbare opties:\n";
    for (const auto &kv : map.locations) {
        std::cout << " - " << kv.first << " (" << kv.second.label << ")\n";
    }
}

void Game::levelUpCmd() {
    levelUp(player_);
}

void Game::saveCmd(const std::string& path) {
    if (saveGame(player_, nodes_, achievements_, path)) {
        std::cout << "Save OK: " << path << "\n";
    } else {
        std::cout << "Save mislukt: " << path << "\n";
    }
}

void Game::loadCmd(const std::string& path) {
    if (loadGame(player_, nodes_, achievements_, path)) {
        std::cout << "Load OK: " << path << "\n";
        if (achievements_.empty()) achievements_ = getDefaultAchievements();
        applyAchievementsToPlayer(player_, achievements_);
    } else {
        std::cout << "Load mislukt: " << path << "\n";
    }
}

bool Game::enterDungeon(const std::string& locationKey) {
    auto itNode = nodes_.find(locationKey);
    if (itNode == nodes_.end()) { std::cout << "Onbekende locatie\n"; return false; }
    Location &loc = itNode->second;
    if (!loc.hasDungeon) { std::cout << "Geen dungeon hier\n"; return false; }
    if (loc.dungeonCleared) { std::cout << "Dungeon al voltooid\n"; return true; }

    // find dungeon by entranceKey
    Dungeon *pd = nullptr;
    for (auto &kv : dungeons_) if (kv.second.entranceKey == locationKey) { pd = &kv.second; break; }
    if (!pd) { std::cout << "Geen dungeon gekoppeld\n"; return false; }
    Dungeon &d = *pd;

    for (const auto &floor : d.floors) {
        std::vector<Enemy> enemies;
        for (int m = 0; m < floor.encounterCount; ++m) {
            Enemy e{"mob", "Gnarl", 8 + 4 * floor.floorIndex, 3 + floor.floorIndex, 1 + floor.floorIndex};
            enemies.push_back(e);
        }
        if (floor.hasBoss) {
            Enemy boss{"boss", "Ancient Guardian", 40 * floor.floorIndex, 8 + floor.floorIndex*2, 5 + floor.floorIndex};
            enemies.push_back(boss);
        }

        BattleContext ctx;
        ctx.allowFlee = true;
        ctx.xpMultiplier = 1.0f;
        BattleResult res = runBattle(player_, enemies, ctx, 0, [&](const BattleEvent& ev){ std::cout << ev.text << "\n"; });

        player_ = res.finalPlayerState;
        if (res.outcome == BattleOutcome::LOSE) {
            std::cout << "Verslagen in dungeon. Je keert terug naar " << locationKey << "\n";
            player_.hp = 1;
            player_.currentLocationKey = locationKey;
            return false;
        } else if (res.outcome == BattleOutcome::FLEE) {
            std::cout << "Je bent gevlucht.\n";
            return false;
        } else {
            std::cout << "Vijanden op deze floor verslagen. Verkregen XP: " << res.xpGained << "\n";
        }
    }

    loc.dungeonCleared = true;
    std::cout << "Dungeon " << d.name << " voltooid! Bonus XP toegekend.\n";
    player_.xp += 100 * d.floorsCount;
    player_.reviveTokens += 1;
    levelUp(player_);
    return true;
}

void Game::run() {
    initWorld();
    runIntro();

    while (true) {
        std::cout << "\n=== Hoofdmenu ===\n"
                     "map            - toon de kaart\n"
                     "trainer        - ga naar de trainer\n"
                     "levelup        - simuleer level-up\n"
                     "rest           - rust uit in de inn van je huidige locatie\n"
                     "enter_loc <key> - betreed de dungeon van gegeven locatie\n"
                     "save <pad>     - sla op naar bestand\n"
                     "load <pad>     - laad spel uit bestand\n"
                     "exit           - afsluiten\n> ";

        std::string line;
        if (!std::getline(std::cin, line)) break;
        line = trim(line);
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        std::string arg;
        if (iss >> std::ws && !iss.eof()) { std::getline(iss, arg); arg = trim(arg); }

        if (cmd == "map") {
            renderMap(nodes_);
        } else if (cmd == "trainer") {
            openTrainer(player_, getAllClasses());
        } else if (cmd == "levelup") {
            levelUpCmd();
        } else if (cmd == "rest") {
            auto it = nodes_.find(player_.currentLocationKey);
            if (it == nodes_.end()) std::cout << "Onbekende locatie.\n";
            else if (!it->second.hasInn) std::cout << "Geen inn hier.\n";
            else { player_.hp = player_.maxHp; std::cout << "HP volledig hersteld.\n"; }
        } else if (cmd == "enter_loc") {
            if (arg.empty()) std::cout << "Gebruik: enter_loc <location_key>\n"; else enterDungeon(arg);
        } else if (cmd == "save") {
            if (arg.empty()) std::cout << "Gebruik: save <pad>\n"; else saveCmd(arg);
        } else if (cmd == "load") {
            if (arg.empty()) std::cout << "Gebruik: load <pad>\n"; else loadCmd(arg);
        } else if (cmd == "exit") {
            std::cout << "Spel afgesloten.\n"; break;
        } else {
            std::cout << "Onbekend commando.\n";
        }
    }
}
