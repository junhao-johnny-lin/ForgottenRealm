// FILE: src/Player.cpp
#include "Player_1_2.h"
#include "Weapon.h"
#include "Armor.h"
#include "achievement_1_2.h"
#include <iostream>

namespace Adventure {

Player::Player()
    : Entity("Player"), level_(1), exp_(0), skillPoints_(0),
      hp_(100), maxHp_(100), inventoryCap_(10), locationIndex_(1),
      class_(ClassType::Knight), equippedWeaponIndex_(-1), equippedArmorIndex_(-1),
      bonusAttack_(0), bonusDefense_(0), bonusHp_(0), bonusExpPercent_(0) {}

Player::Player(std::string name)
    : Entity(std::move(name)), level_(1), exp_(0), skillPoints_(0),
      hp_(100), maxHp_(100), inventoryCap_(10), locationIndex_(1),
      class_(ClassType::Knight), equippedWeaponIndex_(-1), equippedArmorIndex_(-1),
      bonusAttack_(0), bonusDefense_(0), bonusHp_(0), bonusExpPercent_(0) {}

void Player::addItem(std::shared_ptr<Item> it) {
    if ((int)inventory_.size() < inventoryCap_) inventory_.push_back(std::move(it));
}
const std::vector<std::shared_ptr<Item>>& Player::inventory() const { return inventory_; }

bool Player::canEquip(const Item& it) const {
    // if item has allowedClasses, check if player's class is among them
    if (it.type() == ItemType::Weapon) {
        const Weapon* w = dynamic_cast<const Weapon*>(&it);
        if (!w) return true;
        if (w->allowedClasses().empty()) return true;
        for (auto c : w->allowedClasses()) if (c == class_) return true;
        return false;
    } else if (it.type() == ItemType::Armor) {
        const Armor* a = dynamic_cast<const Armor*>(&it);
        if (!a) return true;
        if (a->allowedClasses().empty()) return true;
        for (auto c : a->allowedClasses()) if (c == class_) return true;
        return false;
    }
    return true;
}

void Player::equipWeapon(int invIndex) {
    if (invIndex < 0 || invIndex >= (int)inventory_.size()) return;
    if (inventory_[invIndex]->type() != ItemType::Weapon) return;
    if (!canEquip(*inventory_[invIndex])) { std::cout << "Cannot equip: class restriction\n"; return; }
    equippedWeaponIndex_ = invIndex;
    std::cout << "Equipped " << inventory_[invIndex]->name() << "\n";
}

void Player::equipArmor(int invIndex) {
    if (invIndex < 0 || invIndex >= (int)inventory_.size()) return;
    if (inventory_[invIndex]->type() != ItemType::Armor) return;
    if (!canEquip(*inventory_[invIndex])) { std::cout << "Cannot equip: class restriction\n"; return; }
    equippedArmorIndex_ = invIndex;
    std::cout << "Equipped " << inventory_[invIndex]->name() << "\n";
}

int Player::equippedWeaponDamage() const {
    if (equippedWeaponIndex_ < 0 || equippedWeaponIndex_ >= (int)inventory_.size()) return 1 + bonusAttack_;
    const Weapon* w = dynamic_cast<const Weapon*>(inventory_[equippedWeaponIndex_].get());
    if (!w) return 1 + bonusAttack_;
    return w->damage() + bonusAttack_;
}

int Player::equippedArmorDefense() const {
    if (equippedArmorIndex_ < 0 || equippedArmorIndex_ >= (int)inventory_.size()) return bonusDefense_;
    const Armor* a = dynamic_cast<const Armor*>(inventory_[equippedArmorIndex_].get());
    if (!a) return bonusDefense_;
    return a->defense() + bonusDefense_;
}

void Player::setClass(ClassType c) { class_ = c; }
ClassType Player::characterClass() const { return class_; }

bool Player::learnSkill(const Skill& s) {
    if (skillPoints_ >= s.cost && level_ >= s.requiredLevel) {
        skills_[s.id] = s;
        skillPoints_ -= s.cost;
        return true;
    }
    return false;
}
bool Player::hasSkill(const std::string& id) const { return skills_.count(id) > 0; }

void Player::gainExp(int e) {
    int bonus = e * bonusExpPercent_ / 100;
    e += bonus;
    exp_ += e;
    while (exp_ >= nextLevelExp()) {
        exp_ -= nextLevelExp();
        levelUp();
    }
}

void Player::levelUp() {
    ++level_;
    ++skillPoints_;
    maxHp_ += 10;
    hp_ = maxHp_;
    ++inventoryCap_;
    std::cout << name_ << " leveled up! Now level " << level_ << "\n";
}

int Player::nextLevelExp() const { return 50 + level_ * 30; }
int Player::hp() const { return hp_; }
int Player::maxHp() const { return maxHp_; }
void Player::heal(int amount) { hp_ += amount; if (hp_ > maxHp_) hp_ = maxHp_; }
void Player::takeDamage(int dmg) { hp_ -= dmg; if (hp_ < 0) hp_ = 0; }
int Player::level() const { return level_; }

void Player::applyAchievementBonus(const Achievement& a) {
    bonusAttack_ += a.bonusAttack;
    bonusDefense_ += a.bonusDefense;
    bonusHp_ += a.bonusHp;
    bonusExpPercent_ += a.bonusExpPercent;
    if (a.bonusHp != 0) { maxHp_ += a.bonusHp; hp_ += a.bonusHp; }
}

std::string Player::status() const {
    return name_ + " Class:" + classTypeToString(class_) + " Lvl:" + std::to_string(level_) + " HP:" + std::to_string(hp_) + "/" + std::to_string(maxHp_) +
           " SP:" + std::to_string(skillPoints_) + " EXP:" + std::to_string(exp_) + " Loc:" + std::to_string(locationIndex_);
}

std::vector<std::pair<int,int>> Player::serializeInventory() const {
    std::vector<std::pair<int,int>> out;
    for (const auto& it : inventory_) {
        out.emplace_back(static_cast<int>(it->type()), it->id());
    }
    return out;
}
void Player::deserializeInventory(const std::vector<std::pair<int,int>>& v) {
    inventory_.clear();
    for (const auto& pr : v) {
        int t = pr.first;
        int id = pr.second;
        if (t == static_cast<int>(ItemType::Weapon)) {
            inventory_.push_back(std::make_shared<Weapon>(id, "Loaded Sword"+std::to_string(id), 6 + id%4, 20, ItemRarity::Common));
        } else if (t == static_cast<int>(ItemType::Armor)) {
            inventory_.push_back(std::make_shared<Armor>(id, "Loaded Armor"+std::to_string(id), 2 + id%3, 20, ItemRarity::Common));
        } else {
            inventory_.push_back(std::make_shared<Item>(id, "Loaded Item"+std::to_string(id)));
        }
    }
}

std::vector<std::string> Player::serializeSkills() const {
    std::vector<std::string> out;
    for (const auto& kv : skills_) out.push_back(kv.first);
    return out;
}
void Player::deserializeSkills(const std::vector<std::string>& v) {
    skills_.clear();
    for (const auto& id : v) {
        Skill s; s.id = id; s.name = id; s.cost = 0; s.requiredLevel = 1;
        skills_[id] = s;
    }
}

} // namespace Adventure
