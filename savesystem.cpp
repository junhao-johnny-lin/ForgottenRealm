// FILE: src/SaveSystem.cpp
#include "SaveSystem.h"
#include <fstream>
#include <iostream>

namespace Adventure {

bool SaveSystem::saveAll(const Player& p, const GameWorld& world, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::out);
    if (!ofs) return false;
    ofs << p.name() << "\n";
    ofs << p.classType(); // prints as int
    ofs << " " << p.level() << " " << p.hp() << " " << p.maxHp() << " " << p.locationIndex() << "\n";
    // inventory
    auto inv = p.serializeInventory();
    ofs << inv.size() << "\n";
    for (auto &it : inv) ofs << it.first << " " << it.second << "\n";
    // skills
    auto skills = p.serializeSkills();
    ofs << skills.size() << "\n";
    for (auto &s : skills) ofs << s << "\n";
    // world day
    ofs << world.toSaveDay() << "\n";
    // boss cleared data and dungeon progress not serialized in detail here (can expand)
    ofs.close();
    std::cout << "Saved to " << filename << "\n";
    return true;
}

bool SaveSystem::loadAll(Player& p, GameWorld& world, const std::string& filename) {
    std::ifstream ifs(filename, std::ios::in);
    if (!ifs) return false;
    std::string name;
    std::getline(ifs, name);
    int classInt = 0;
    int level,hp,maxhp,loc;
    ifs >> classInt >> level >> hp >> maxhp >> loc;
    Player tmp(name);
    tmp.setClass(static_cast<ClassType>(classInt));
    for (int i=1;i<level;i++) tmp.levelUp();
    tmp.setLocationIndex(loc);
    // inventory
    int invCount; ifs >> invCount;
    std::vector<std::pair<int,int>> inv;
    for (int i=0;i<invCount;i++) { int t,id; ifs >> t >> id; inv.emplace_back(t,id); }
    tmp.deserializeInventory(inv);
    // skills
    int skillCount; ifs >> skillCount; std::string dummy; std::getline(ifs,dummy);
    std::vector<std::string> skills;
    for (int i=0;i<skillCount;i++) { std::string s; std::getline(ifs,s); if(!s.empty()) skills.push_back(s); }
    tmp.deserializeSkills(skills);
    // world day
    int day; ifs >> day; world.fromLoadDay(day);
    p = tmp;
    std::cout << "Loaded player " << p.name() << "\n";
    return true;
}

} // namespace Adventure
