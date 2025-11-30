// FILE: src/Armor.cpp
#include "Armor.h"
#include <sstream>

namespace Adventure {

Armor::Armor() : Item(), defense_(0), durability_(10) { type_ = ItemType::Armor; }
Armor::Armor(int id, std::string name, int def, int dur, ItemRarity r, std::vector<ClassType> allowed)
    : Item(id, std::move(name), ItemType::Armor, r), defense_(def), durability_(dur), allowedClasses_(std::move(allowed)) {}
Armor::Armor(const Armor& other)
    : Item(other.id_, other.name_, other.type_, other.rarity_), defense_(other.defense_), durability_(other.durability_), allowedClasses_(other.allowedClasses_) {}
Armor::~Armor() = default;

std::string Armor::use() {
    std::ostringstream ss;
    ss << "Equipped " << name_ << " (DEF " << defense_ << ")";
    return ss.str();
}
int Armor::defense() const { return defense_; }
int Armor::durability() const { return durability_; }
void Armor::takeHit(int amount) { durability_ -= amount; if (durability_ < 0) durability_ = 0; }
const std::vector<ClassType>& Armor::allowedClasses() const { return allowedClasses_; }

} // namespace Adventure
