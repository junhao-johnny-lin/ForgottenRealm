// FILE: savesystem.cpp
#include "savesystem.h"
#include "player_1_2.h"
#include "gameworld.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include <fstream>
#include <iostream>

namespace Adventure {

bool SaveSystem::saveAll(const Player& p, const GameWorld& w, const std::string& path)
{
    std::ofstream ofs(path);
    if (!ofs) {
        std::cerr << "ERROR: Cannot open save file.\n";
        return false;
    }

    // -------------------------
    // PLAYER CORE
    // -------------------------
    ofs << p.name() << "\n";
    ofs << p.level() << " " << p.exp() << "\n";
    ofs << p.hp() << " " << p.maxHp() << "\n";
    ofs << p.day() << "\n";

    // -------------------------
    // CLASS PROGRESSION
    // -------------------------
    ofs << static_cast<int>(p.baseClass())     << " "
        << static_cast<int>(p.advancedClass()) << " "
        << static_cast<int>(p.ultimateClass()) << " "
        << static_cast<int>(p.hiddenClass())   << "\n";

    // -------------------------
    // SKILLS  (NO LEVEL)
    // -------------------------
    ofs << p.learnedSkills().size() << "\n";
    for (auto& s : p.learnedSkills()) {
        ofs << s.first << "\n";   // ONLY SKILL ID
    }

    // -------------------------
    // INVENTORY
    // -------------------------
    ofs << p.inventory().size() << "\n";
    for (auto& it : p.inventory()) {

        ofs << static_cast<int>(it->type()) << " ";

        // Weapon
        if (it->type() == ItemType::Weapon) {
            Weapon* wpn = (Weapon*)it.get();
            ofs << wpn->name() << " "
                << wpn->damage() << " "
                << static_cast<int>(wpn->rarity()) << "\n";
        }

        // Armor
        else if (it->type() == ItemType::Armor) {
            Armor* arm = (Armor*)it.get();
            ofs << arm->name() << " "
                << arm->defense() << " "
                << static_cast<int>(arm->rarity()) << "\n";
        }

        // Generic Item
        else {
            ofs << it->name() << " "
                << static_cast<int>(it->rarity()) << "\n";
        }
    }

    // -------------------------
    // WORLD
    // -------------------------
    int dungeonCount = 0;
    for (int i = 0; i < 50; i++)
        if (w.isDungeonCleared(i)) dungeonCount++;

    ofs << dungeonCount << "\n";

    for (int i = 0; i < 50; i++)
        if (w.isDungeonCleared(i))
            ofs << i << "\n";

    // boss clears
    for (int i = 0; i < 50; i++)
        ofs << (w.isBossCleared(i) ? 1 : 0) << " ";

    ofs << "\n";
    return true;
}



bool SaveSystem::loadAll(Player& p, GameWorld& w, const std::string& path)
{
    std::ifstream ifs(path);
    if (!ifs) {
        std::cerr << "ERROR: Cannot open save file.\n";
        return false;
    }

    // -------------------------
    // PLAYER CORE
    // -------------------------
    std::string nm;
    std::getline(ifs, nm);
    if (nm.empty()) return false;

    int lvl, exp, hp, maxHp, days;
    ifs >> lvl >> exp;
    ifs >> hp >> maxHp;
    ifs >> days;

    p.overrideName(nm);
    p.overrideLevel(lvl);
    p.overrideExp(exp);
    p.overrideHp(hp, maxHp);
    p.setDay(days);

    // -------------------------
    // CLASS PROGRESSION
    // -------------------------
    int b,a,u,h;
    ifs >> b >> a >> u >> h;

    p.overrideBaseClass((ClassType)b);
    p.unlockAdvanced((ClassType)a);
    p.unlockUltimate((ClassType)u);
    p.unlockHidden((ClassType)h);

    // -------------------------
    // SKILLS (NO LEVEL)
    // -------------------------
    size_t sc;
    ifs >> sc;

    for (size_t i = 0; i < sc; i++) {
        std::string id;
        ifs >> id;

        const Skill* sk = SkillTree::instance().skillById(id);
        if (sk)
            p.forceLearnSkill(id, sk->requiredLevel);
        else
            p.forceLearnSkill(id, 1);
    }

    // -------------------------
    // INVENTORY
    // -------------------------
    size_t ic;
    ifs >> ic;

    for (size_t i = 0; i < ic; i++) {
        int t;
        ifs >> t;

        std::string nm2;
        int v1, v2;
        ifs >> nm2 >> v1 >> v2;

        if (t == (int)ItemType::Weapon)
            p.addItem(std::make_shared<Weapon>(nm2, v1, (ItemRarity)v2));
        else if (t == (int)ItemType::Armor)
            p.addItem(std::make_shared<Armor>(nm2, v1, (ItemRarity)v2));
        else
            p.addItem(std::make_shared<Item>(nm2, (ItemRarity)v2));
    }

    // -------------------------
    // WORLD
    // -------------------------
    size_t clearedCount;
    ifs >> clearedCount;

    for (size_t i = 0; i < clearedCount; i++) {
        int id;
        ifs >> id;
        w.setDungeonCleared(id, true);
    }

    for (int i = 0; i < 50; i++) {
        int v;
        ifs >> v;
        w.setBossCleared(i, v != 0);
    }

    return true;
}

} // namespace Adventure
