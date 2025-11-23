// save.cpp
#include "save.h"
#include "items.h"
#include "loot.h"
#include "achievements.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

// Save game to path. Weapons are written as: id|type|tier|durability
bool saveGame(const std::string& path,
              const std::vector<WeaponInstance>& weapons,
              const std::vector<Potion>& potions,
              const std::vector<Achievement>& achievements) {
    std::ofstream os(path, std::ios::out | std::ios::trunc);
    if (!os) {
        std::cerr << "Failed to open save file for writing: " << path << "\n";
        return false;
    }

    os << "[weapons]\n";
    for (const auto& w : weapons) {
        os << w.id << "|" << w.type << "|" << w.tier << "|" << w.durability << "\n";
    }

    os << "[potions]\n";
    for (const auto& p : potions) {
        os << p.id << "|" << p.potency << "|" << (p.permanent ? "1" : "0") << "\n";
    }

    os << "[achievements]\n";
    for (const auto& a : achievements) {
        os << a.id << "|" << (a.unlocked ? "1" : "0") << "\n";
    }

    return true;
}

// Load game from path. Existing containers are appended to.
bool loadGame(const std::string& path,
              std::vector<WeaponInstance>& weapons,
              std::vector<Potion>& potions,
              std::vector<Achievement>& achievements) {
    std::ifstream is(path);
    if (!is) {
        std::cerr << "Failed to open save file for reading: " << path << "\n";
        return false;
    }

    std::string line;
    enum class Section { None, Weapons, Potions, Achievements } sec = Section::None;

    while (std::getline(is, line)) {
        if (line == "[weapons]") { sec = Section::Weapons; continue; }
        if (line == "[potions]") { sec = Section::Potions; continue; }
        if (line == "[achievements]") { sec = Section::Achievements; continue; }

        if (sec == Section::Weapons) {
            // format: id|type|tier|dur
            size_t p1 = line.find('|');
            size_t p2 = (p1 == std::string::npos) ? std::string::npos : line.find('|', p1 + 1);
            size_t p3 = (p2 == std::string::npos) ? std::string::npos : line.find('|', p2 + 1);
            if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos) continue;
            std::string id = line.substr(0, p1);
            std::string type = line.substr(p1 + 1, p2 - p1 - 1);
            // tier in file is numeric but we reconstruct using makeWeaponInstanceFromTierId by id
            int tier = std::stoi(line.substr(p2 + 1, p3 - p2 - 1));
            int dur = std::stoi(line.substr(p3 + 1));
            WeaponInstance wi = makeWeaponInstanceFromTierId(id, type, "", -1, dur);
            weapons.push_back(std::move(wi));
        } else if (sec == Section::Potions) {
            // format: id|potency|perm
            size_t p1 = line.find('|');
            size_t p2 = (p1 == std::string::npos) ? std::string::npos : line.find('|', p1 + 1);
            if (p1 == std::string::npos || p2 == std::string::npos) continue;
            Potion p;
            p.id = line.substr(0, p1);
            p.potency = std::stoi(line.substr(p1 + 1, p2 - p1 - 1));
            p.permanent = (line.substr(p2 + 1) == "1");
            potions.push_back(std::move(p));
        } else if (sec == Section::Achievements) {
            size_t p = line.find('|');
            if (p == std::string::npos) continue;
            std::string id = line.substr(0, p);
            bool unlocked = (line.substr(p + 1) == "1");
            auto it = std::find_if(achievements.begin(), achievements.end(), [&](Achievement& a){ return a.id == id; });
            if (it != achievements.end()) it->unlocked = unlocked;
        }
    }

    return true;
}
