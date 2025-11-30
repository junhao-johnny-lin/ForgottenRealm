// FILE: src/SaveSystem.cpp
// Ultimate SaveSystem (option D). Uses /mnt/data/Document.pdf as specification reference.
#include "SaveSystem.h"
#include "Player_1_2.h"
#include "GameWorld.h"
#include "Weapon.h"
#include "Armor.h"
#include "Item.h"
#include "Skills_1_2.h"

#include <fstream>
#include <iostream>

namespace Adventure {

static void writeStringEscaped(std::ofstream& ofs, const std::string& s) {
    // simple escaping: write length then string (avoids spaces/newline issues)
    ofs << s.size() << " " << s << "\n";
}

static std::string readStringEscaped(std::ifstream& ifs) {
    size_t len = 0;
    ifs >> len;
    std::string tmp;
    ifs.get(); // consume space
    tmp.resize(len);
    ifs.read(&tmp[0], len);
    ifs.get(); // consume newline
    return tmp;
}

bool SaveSystem::saveAll(const Player& p, const GameWorld& w, const std::string& path) {
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs) {
        std::cerr << "SaveSystem: cannot open " << path << " for writing\n";
        return false;
    }

    // HEADER (version)
    ofs << "FRSV1\n";

    // Player basic
    writeStringEscaped(ofs, p.name());
    ofs << p.level() << " " << p.exp() << "\n";
    ofs << p.hp() << " " << p.maxHp() << "\n";
    ofs << p.skillPoints() << "\n";
    ofs << p.day() << "\n";

    // Classes
    ofs << static_cast<int>(p.baseClass()) << " "
        << static_cast<int>(p.advancedClass()) << " "
        << static_cast<int>(p.ultimateClass()) << " "
        << static_cast<int>(p.hiddenClass()) << "\n";

    // Learned skills
    const auto& skills = p.learnedSkills();
    ofs << skills.size() << "\n";
    for (const auto& kv : skills) {
        writeStringEscaped(ofs, kv.first);          // id
        ofs << kv.second.requiredLevel << " "      // saved level/requiredLevel slot
            << kv.second.cost << " "               // cost
            << kv.second.power << "\n";
    }

    // Inventory (serialize each item minimally)
    const auto& inv = p.inventory();
    ofs << inv.size() << "\n";
    for (const auto& it : inv) {
        ofs << static_cast<int>(it->type()) << " ";
        writeStringEscaped(ofs, it->name());
        ofs << it->rarity() << " ";
        // For Weapon/Armor, write class-allowlist and stats
        if (it->type() == ItemType::Weapon) {
            const Weapon* wpn = dynamic_cast<const Weapon*>(it.get());
            ofs << wpn->damage() << " " << (int)wpn->durability() << " ";
            // allowed classes
            const auto& list = wpn->allowedClasses();
            ofs << list.size() << " ";
            for (auto c : list) ofs << static_cast<int>(c) << " ";
            ofs << "\n";
        } else if (it->type() == ItemType::Armor) {
            const Armor* arm = dynamic_cast<const Armor*>(it.get());
            ofs << arm->defense() << " " << (int)arm->durability() << " ";
            const auto& list = arm->allowedClasses();
            ofs << list.size() << " ";
            for (auto c : list) ofs << static_cast<int>(c) << " ";
            ofs << "\n";
        } else {
            ofs << "0\n";
        }
    }

    // Equipped items (store by index in inventory or by name)
    // We'll write weapon name and armor name (or empty)
    writeStringEscaped(ofs, p.weapon() ? p.weapon()->name() : std::string());
    writeStringEscaped(ofs, p.armor() ? p.armor()->name() : std::string());

    // GameWorld: days and dungeon progress
    ofs << w.day() << "\n";
    auto cleared = w.clearedDungeons();
    ofs << cleared.size() << "\n";
    for (const auto& id : cleared) writeStringEscaped(ofs, id);

    // boss stats
    ofs << w.lastBossHp() << " " << w.lastBossAtk() << " " << w.lastBossDef() << " " << w.lastBossSpeed() << "\n";

    // achievements
    auto ach = w.achievements();
    ofs << ach.size() << "\n";
    for (const auto& kv : ach) {
        writeStringEscaped(ofs, kv.first);
        ofs << (kv.second ? 1 : 0) << "\n";
    }

    ofs.close();
    return true;
}

bool SaveSystem::loadAll(Player& p, GameWorld& w, const std::string& path) {
    std::ifstream ifs(path, std::ios::binary);
    if (!ifs) {
        std::cerr << "SaveSystem: cannot open " << path << " for reading\n";
        return false;
    }

    std::string header;
    std::getline(ifs, header);
    if (header != "FRSV1") {
        std::cerr << "SaveSystem: unknown save header\n";
        return false;
    }

    // Player basic
    std::string pname = readStringEscaped(ifs);
    int lvl, xp;
    ifs >> lvl >> xp;
    int hp, maxhp;
    ifs >> hp >> maxhp;
    int sp; ifs >> sp;
    int day; ifs >> day;
    p.overrideName(pname);
    p.overrideLevel(lvl);
    p.overrideExp(xp);
    p.overrideHp(hp, maxhp);
    p.setSkillPoints(sp);
    p.setDay(day);

    // Classes
    int b,a,uu,h;
    ifs >> b >> a >> uu >> h;
    p.overrideBaseClass(static_cast<ClassType>(b));
    p.unlockAdvanced(static_cast<ClassType>(a));
    p.unlockUltimate(static_cast<ClassType>(uu));
    p.unlockHidden(static_cast<ClassType>(h));

    // skills
    size_t sval;
    ifs >> sval;
    for (size_t i=0;i<sval;++i) {
        std::string id = readStringEscaped(ifs);
        int rl, cost, power;
        ifs >> rl >> cost >> power;
        p.forceLearnSkill(id, rl);
    }

    // inventory
    size_t invc;
    ifs >> invc;
    for (size_t i=0;i<invc;++i) {
        int typeInt; ifs >> typeInt;
        std::string iname = readStringEscaped(ifs);
        int rarity; ifs >> rarity;
        if (typeInt == (int)ItemType::Weapon) {
            int dmg, dur; ifs >> dmg >> dur;
            size_t acl; ifs >> acl;
            std::vector<ClassType> allowed;
            for (size_t j=0;j<acl;++j) { int ci; ifs >> ci; allowed.push_back(static_cast<ClassType>(ci)); }
            auto wptr = std::make_shared<Weapon>(1000+(int)i, iname, dmg, dur, static_cast<ItemRarity>(rarity), allowed);
            p.addItem(wptr);
        } else if (typeInt == (int)ItemType::Armor) {
            int df, dur; ifs >> df >> dur;
            size_t acl; ifs >> acl;
            std::vector<ClassType> allowed;
            for (size_t j=0;j<acl;++j) { int ci; ifs >> ci; allowed.push_back(static_cast<ClassType>(ci)); }
            auto ap = std::make_shared<Armor>(2000+(int)i, iname, df, dur, static_cast<ItemRarity>(rarity), allowed);
            p.addItem(ap);
        } else {
            int zero; ifs >> zero;
        }
    }

    // equipped names
    std::string wname = readStringEscaped(ifs);
    std::string aname = readStringEscaped(ifs);
    // try to equip by name (linear search)
    for (auto& it : p.inventory()) {
        if (!wname.empty() && it->type() == ItemType::Weapon && it->name() == wname) {
            p.equipWeapon(std::dynamic_pointer_cast<Weapon>(it));
        }
        if (!aname.empty() && it->type() == ItemType::Armor && it->name() == aname) {
            p.equipArmor(std::dynamic_pointer_cast<Armor>(it));
        }
    }

    // GameWorld
    int gday; ifs >> gday; w.fromLoadDay(gday);
    size_t clearedCount; ifs >> clearedCount;
    for (size_t i=0;i<clearedCount;++i) {
        std::string id = readStringEscaped(ifs);
        w.markDungeonCleared(id);
    }

    int bh,ba,bd,bs; ifs >> bh >> ba >> bd >> bs;
    w.setLastBossStats(bh,ba,bd,bs);

    size_t achCount; ifs >> achCount;
    for (size_t i=0;i<achCount;++i) {
        std::string id = readStringEscaped(ifs);
        int unlocked; ifs >> unlocked;
        w.forceAchievement(id, unlocked != 0);
    }

    ifs.close();
    return true;
}

} // namespace Adventure
