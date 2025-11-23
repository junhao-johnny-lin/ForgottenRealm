// FILE: include/Player.h
#pragma once
#include "Entity.h"
#include "Item.h"
#include "Skills_1_2.h"
#include "Enums.h"
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "achievement_1_2.h"

namespace Adventure {

class Player : public Entity {
public:
    Player();
    explicit Player(std::string name);

    void update() override {}

    // inventory & equip
    void addItem(std::shared_ptr<Item> it);
    const std::vector<std::shared_ptr<Item>>& inventory() const;
    bool canEquip(const Item& it) const;
    void equipWeapon(int invIndex); // simple equip by inventory index (weapon)
    void equipArmor(int invIndex);
    int equippedWeaponDamage() const;
    int equippedArmorDefense() const;

    // classes & skills
    void setClass(ClassType c);
    ClassType characterClass() const;
    bool learnSkill(const Skill& s);
    bool hasSkill(const std::string& id) const;

    // leveling
    void gainExp(int e);
    void levelUp();
    int nextLevelExp() const;

    // HP & combat
    int hp() const;
    int maxHp() const;
    void heal(int amount);
    void takeDamage(int dmg);
    int level() const;

    // achievements
    void applyAchievementBonus(const Achievement& a);

    std::string status() const;

    // serialization helpers
    std::vector<std::pair<int,int>> serializeInventory() const; // pair<type,id>
    void deserializeInventory(const std::vector<std::pair<int,int>>& v);
    std::vector<std::string> serializeSkills() const;
    void deserializeSkills(const std::vector<std::string>& v);
    void setLocationIndex(int idx) { locationIndex_ = idx; }
    int locationIndex() const { return locationIndex_; }

    ClassType classType() const { return class_; }

private:
    int level_;
    int exp_;
    int skillPoints_;
    int hp_;
    int maxHp_;
    int inventoryCap_;
    int locationIndex_;
    std::vector<std::shared_ptr<Item>> inventory_;
    std::map<std::string, Skill> skills_;
    ClassType class_;
    // equipment indices in inventory (-1 none)
    int equippedWeaponIndex_;
    int equippedArmorIndex_;
    // permanent bonuses
    int bonusAttack_;
    int bonusDefense_;
    int bonusHp_;
    int bonusExpPercent_;
};

} // namespace Adventure
