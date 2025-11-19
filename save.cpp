#include "save.h"
#include <fstream>
#include <sstream>
#include <algorithm>

bool saveGameState(const std::string& path,
                   const std::unordered_map<std::string, Location>& nodes,
                   const std::vector<Achievement>& achievements,
                   const PlayerState& player,
                   const std::string& lastNewDungeonBossId,
                   int lastBossKillDay)
{
    std::ofstream out(path);
    if (!out) return false;
    out << "#PLAYER " << player.hp << "|" << player.maxHp << "|" << player.attack << "|" << player.defence
        << "|" << player.xp << "|" << player.level << "|" << player.skillPoints << "|" << player.classId
        << "|" << player.reviveTokens << "|" << player.dayCount << "|" << player.currentLocationKey << "\n";
    out << "#LASTBOSS " << lastNewDungeonBossId << "|" << lastBossKillDay << "\n";

    out << "#NODES\n";
    for (const auto &kv : nodes) {
        const auto &n = kv.second;
        out << n.key << '|' << (n.explored? "1":"0") << '|' << (n.defeated? "1":"0") << '|' << (n.current? "1":"0") << '\n';
    }
    out << "#ACHS\n";
    for (const auto &a : achievements) {
        out << a.id << '|' << (a.unlocked? "1":"0") << '\n';
    }
    out << "#CLASS_SKILLS\n";
    for (const auto &sid : player.unlockedClassSkills) out << sid << "\n";
    return true;
}

bool loadGameState(const std::string& path,
                   std::unordered_map<std::string, Location>& nodes,
                   std::vector<Achievement>& achievements,
                   PlayerState& player,
                   std::string& lastNewDungeonBossId,
                   int& lastBossKillDay)
{
    std::ifstream in(path);
    if (!in) return false;
    std::string line;
    enum Section { NONE, NODES, ACHS, CLASS_SKILLS } sec = NONE;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        if (line.rfind("#PLAYER ",0)==0) {
            std::istringstream iss(line.substr(8));
            std::string hp,maxhp,atk,def,xp,lvl,sp,classId,rt,days,loc;
            std::getline(iss,hp,'|'); std::getline(iss,maxhp,'|'); std::getline(iss,atk,'|'); std::getline(iss,def,'|');
            std::getline(iss,xp,'|'); std::getline(iss,lvl,'|'); std::getline(iss,sp,'|'); std::getline(iss,classId,'|');
            std::getline(iss,rt,'|'); std::getline(iss,days,'|'); std::getline(iss,loc,'|');
            player.hp = std::stoi(hp); player.maxHp = std::stoi(maxhp); player.attack = std::stoi(atk); player.defence = std::stoi(def);
            player.xp = std::stoi(xp); player.level = std::stoi(lvl); player.skillPoints = std::stoi(sp); player.classId = classId;
            player.reviveTokens = std::stoi(rt); player.dayCount = std::stoi(days); player.currentLocationKey = loc;
        } else if (line.rfind("#LASTBOSS ",0)==0) {
            std::istringstream iss(line.substr(10));
            std::string id, day;
            std::getline(iss,id,'|'); std::getline(iss,day,'|');
            lastNewDungeonBossId = id; lastBossKillDay = std::stoi(day);
        } else if (line == "#NODES") { sec = NODES; }
        else if (line == "#ACHS") { sec = ACHS; }
        else if (line == "#CLASS_SKILLS") { sec = CLASS_SKILLS; }
        else if (sec == NODES) {
            std::istringstream iss(line);
            std::string k,e,d,c;
            std::getline(iss,k,'|'); std::getline(iss,e,'|'); std::getline(iss,d,'|'); std::getline(iss,c,'|');
            auto it = nodes.find(k);
            if (it != nodes.end()) {
                it->second.explored = (e=="1");
                it->second.defeated = (d=="1");
                it->second.current = (c=="1");
            }
        } else if (sec == ACHS) {
            std::istringstream iss(line);
            std::string id, u;
            std::getline(iss,id,'|'); std::getline(iss,u,'|');
            auto it = std::find_if(achievements.begin(), achievements.end(), [&](const Achievement& a){return a.id==id;});
            if (it != achievements.end()) it->unlocked = (u=="1");
        } else if (sec == CLASS_SKILLS) {
            player.unlockedClassSkills.push_back(line);
        }
    }
    return true;
}
