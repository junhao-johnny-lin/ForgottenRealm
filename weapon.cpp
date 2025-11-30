// FILE: src/Weapon.cpp
#include "Weapon.h"
#include <sstream>

namespace Adventure {

Weapon::Weapon() : Item(), damage_(1), durability_(10) { type_ = ItemType::Weapon; }
Weapon::Weapon(int id, std::string name, int dmg, int dur, ItemRarity r, std::vector<ClassType> allowed)
    : Item(id, std::move(name), ItemType::Weapon, r), damage_(dmg), durability_(dur), allowedClasses_(std::move(allowed)) {}
Weapon::Weapon(const Weapon& other)
    : Item(other.id_, other.name_, other.type_, other.rarity_), damage_(other.damage_), durability_(other.durability_), allowedClasses_(other.allowedClasses_) {}
Weapon::~Weapon() = default;

std::string Weapon::use() {
    if (durability_ <= 0) return name_ + " is broken";
    --durability_;
    std::ostringstream ss;
    ss << name_ << " deals " << damage_ << " dmg. Durability: " << durability_;
    return ss.str();
}

int Weapon::damage() const { return damage_; }
int Weapon::durability() const { return durability_; }
void Weapon::repair(int amount) { durability_ += amount; }
const std::vector<ClassType>& Weapon::allowedClasses() const { return allowedClasses_; }

} // namespace Adventure
