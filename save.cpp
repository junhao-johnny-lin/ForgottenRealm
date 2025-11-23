#include "save.h"
#include <fstream>
#include <sstream>
#include <iostream>

static inline const char* boolToStr(bool v) { return v ? "1" : "0"; }
static inline bool strToBool(const std::string& s) { return !s.empty() && s[0] == '1'; }

bool saveGame(const PlayerState& player,
              const std::unordered_map<std::string, Location>& nodes,
              const std::vector<Achievement>& achievements,
              const std::string& path)
{
    std::ofstream f(path);
    if (!f) return false;

    // PLAYER
    f << "SECTION=PLAYER\n";
    f << player.classId << "|" << player.level << "|" << player.xp << "|" << player.skillPoints << "|"
      << player.maxHp << "|" << player.hp << "|" << player.attack << "|" << player.defence << "|"
      << player.currentLocationKey << "|" << player.reviveTokens << "\n";

    // NODES
    f << "SECTION=NODES\n";
    for (const auto& kv : nodes) {
        const auto& k = kv.first;
        const auto& n = kv.second;
        f << k << "|" << n.label << "|" << boolToStr(n.visited) << "|" << boolToStr(n.accessible) << "|"
          << boolToStr(n.hasTrainer) << "|" << boolToStr(n.hasCamp) << "|" << boolToStr(n.hasDungeon) << "|"
          << boolToStr(n.hasInn) << "|" << boolToStr(n.dungeonCleared) << "\n";
    }

    // ACHIEVEMENTS: format:
    // id|name|description|unlocked|hp;strength;defence;mana;speed;intelligence|key1=val,key2=val
    f << "SECTION=ACHIEVEMENTS\n";
    for (const auto& a : achievements) {
        f << a.id << "|" << a.name << "|" << a.description << "|" << (a.unlocked ? "1" : "0") << "|";
        f << a.mods.hp << ";" << a.mods.strength << ";" << a.mods.defence << ";" << a.mods.mana << ";" << a.mods.speed << ";" << a.mods.intelligence << "|";
        bool first = true;
        for (const auto &kv : a.flags) {
            if (!first) f << ",";
            f << kv.first << "=" << kv.second;
            first = false;
        }
        f << "\n";
    }

    return true;
}

bool loadGame(PlayerState& player,
              std::unordered_map<std::string, Location>& nodes,
              std::vector<Achievement>& achievements,
              const std::string& path)
{
    std::ifstream f(path);
    if (!f) return false;

    std::string line;
    std::string section;
    nodes.clear();
    achievements.clear();

    while (std::getline(f, line)) {
        if (line.rfind("SECTION=",0) == 0) { section = line.substr(8); continue; }
        if (section == "PLAYER") {
            std::istringstream iss(line);
            std::string cls;
            int level=1, xp=0, sp=0, maxHp=20, hp=20, atk=0, def=0;
            std::string loc; int rev=0;

            if (!std::getline(iss, cls, '|')) continue;
            auto nextInt = [&](int &out)->bool {
                std::string token;
                if (!std::getline(iss, token, '|')) return false;
                try { out = std::stoi(token); } catch(...) { out = 0; }
                return true;
            };

            // tokens may be separated by '|' as expected in saveGame
            std::string token;
            if (!std::getline(iss, token, '|')) continue; // level
            try { level = std::stoi(token); } catch(...) { level = 1; }
            if (!std::getline(iss, token, '|')) continue; try { xp = std::stoi(token); } catch(...) { xp = 0; }
            if (!std::getline(iss, token, '|')) continue; try { sp = std::stoi(token); } catch(...) { sp = 0; }
            if (!std::getline(iss, token, '|')) continue; try { maxHp = std::stoi(token); } catch(...) { maxHp = 20; }
            if (!std::getline(iss, token, '|')) continue; try { hp = std::stoi(token); } catch(...) { hp = maxHp; }
            if (!std::getline(iss, token, '|')) continue; try { atk = std::stoi(token); } catch(...) { atk = 0; }
            if (!std::getline(iss, token, '|')) continue; try { def = std::stoi(token); } catch(...) { def = 0; }
            if (!std::getline(iss, loc, '|')) loc = "";
            if (!std::getline(iss, token, '|')) token = "0"; try { rev = std::stoi(token); } catch(...) { rev = 0; }

            player.classId = cls;
            player.level = level;
            player.xp = xp;
            player.skillPoints = sp;
            player.maxHp = maxHp;
            player.hp = hp;
            player.attack = atk;
            player.defence = def;
            player.currentLocationKey = loc;
            player.reviveTokens = rev;

        } else if (section == "NODES") {
            std::istringstream iss(line);
            std::string key,label,vVisited,vAccessible,vTrainer,vCamp,vHasDungeon,vHasInn,vDungeonCleared;
            if (!std::getline(iss,key,'|')) continue;
            if (!std::getline(iss,label,'|')) continue;
            if (!std::getline(iss,vVisited,'|')) continue;
            if (!std::getline(iss,vAccessible,'|')) continue;
            if (!std::getline(iss,vTrainer,'|')) continue;
            if (!std::getline(iss,vCamp,'|')) continue;
            if (!std::getline(iss,vHasDungeon,'|')) continue;
            if (!std::getline(iss,vHasInn,'|')) continue;
            if (!std::getline(iss,vDungeonCleared,'|')) vDungeonCleared = "0";

            Location n;
            n.label = label;
            n.visited = strToBool(vVisited);
            n.accessible = strToBool(vAccessible);
            n.hasTrainer = strToBool(vTrainer);
            n.hasCamp = strToBool(vCamp);
            n.hasDungeon = strToBool(vHasDungeon);
            n.hasInn = strToBool(vHasInn);
            n.dungeonCleared = strToBool(vDungeonCleared);
            nodes[key] = n;

        } else if (section == "ACHIEVEMENTS") {
            std::istringstream iss(line);
            std::string id,name,description,unlockedStr,modsStr,flagsStr;
            if (!std::getline(iss,id,'|')) continue;
            if (!std::getline(iss,name,'|')) continue;
            if (!std::getline(iss,description,'|')) continue;
            if (!std::getline(iss,unlockedStr,'|')) continue;
            if (!std::getline(iss,modsStr,'|')) continue;
            if (!std::getline(iss,flagsStr)) flagsStr = "";

            Achievement a;
            a.id = id;
            a.name = name;
            a.description = description;
            a.unlocked = (!unlockedStr.empty() && unlockedStr[0]=='1');

            // parse mods: hp;strength;defence;mana;speed;intelligence
            std::istringstream mss(modsStr);
            std::string token;
            auto nextInt = [&]()->int {
                if (!std::getline(mss, token, ';')) return 0;
                try { return std::stoi(token); } catch(...) { return 0; }
            };
            a.mods.hp = nextInt();
            a.mods.strength = nextInt();
            a.mods.defence = nextInt();
            a.mods.mana = nextInt();
            a.mods.speed = nextInt();
            a.mods.intelligence = nextInt();

            // parse flags k=v,k2=v2
            a.flags.clear();
            std::istringstream fss(flagsStr);
            while (std::getline(fss, token, ',')) {
                if (token.empty()) continue;
                auto pos = token.find('=');
                if (pos==std::string::npos) continue;
                std::string k = token.substr(0,pos);
                int v = 0;
                try { v = std::stoi(token.substr(pos+1)); } catch(...) { v = 0; }
                a.flags[k] = v;
            }
            achievements.push_back(a);
        }
    }

    return true;
}
