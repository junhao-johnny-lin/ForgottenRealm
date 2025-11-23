// FILE: include/Armor.h
#pragma once
#include "Item.h"
#include "Enums.h"
#include <string>
#include <vector>

namespace Adventure {

class Armor : public Item {
public:
    Armor() : Item(), defense_(0), durability_(10) { type_ = ItemType::Armor; }
    Armor(int id, std::string name, int def, int dur, ItemRarity r = ItemRarity::Common,
          std::vector<ClassType> allowed = {})
        : Item(id, std::move(name), ItemType::Armor, r), defense_(def), durability_(dur), allowedClasses_(std::move(allowed)) {}
    ~Armor() override = default;

    std::string use() override { return "Equipped " + name_; }
    int defense() const { return defense_; }
    int durability() const { return durability_; }
    void takeHit(int amount) { durability_ -= amount; if (durability_ < 0) durability_ = 0; }
    const std::vector<ClassType>& allowedClasses() const { return allowedClasses_; }

private:
    int defense_;
    int durability_;
    std::vector<ClassType> allowedClasses_;
};

} // namespace Adventure
