// FILE: include/Weapon.h
#pragma once
#include "Item.h"
#include "Enums.h"
#include <string>
#include <vector>

namespace Adventure {

class Weapon : public Item {
public:
    Weapon() : Item(), damage_(1), durability_(10) { type_ = ItemType::Weapon; }
    Weapon(int id, std::string name, int dmg, int dur, ItemRarity r = ItemRarity::Common,
           std::vector<ClassType> allowed = {})
        : Item(id, std::move(name), ItemType::Weapon, r), damage_(dmg), durability_(dur), allowedClasses_(std::move(allowed)) {}
    ~Weapon() override = default;

    std::string use() override {
        if (durability_ <= 0) return name_ + " is broken";
        --durability_;
        return name_ + " used for " + std::to_string(damage_) + " damage";
    }

    int damage() const { return damage_; }
    int durability() const { return durability_; }
    void repair(int amount) { durability_ += amount; }
    const std::vector<ClassType>& allowedClasses() const { return allowedClasses_; }

private:
    int damage_;
    int durability_;
    std::vector<ClassType> allowedClasses_;
};

} // namespace Adventure
