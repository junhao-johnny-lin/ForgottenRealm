#include "Weapon.h"

namespace Adventure {

Weapon::Weapon()
    : Item(0, "Unnamed Weapon", ItemRarity::Common),
      damage_(1), durability_(100) {}

Weapon::Weapon(int id, std::string name, int dmg, int dur, ItemRarity r, std::vector<ClassType> allowed)
    : Item(id, name, r),
      damage_(dmg), durability_(dur),
      allowedClasses_(std::move(allowed)) {}

// ➕ ADD THIS (used by SaveSystem)
Weapon::Weapon(std::string name, int dmg, ItemRarity r)
    : Item(0, name, r),
      damage_(dmg),
      durability_(100),
      allowedClasses_({})
{}

Weapon::Weapon(const Weapon& other) = default;
Weapon::~Weapon() = default;

std::string Weapon::use() { return "Swing!"; }
int Weapon::damage() const { return damage_; }
int Weapon::durability() const { return durability_; }
void Weapon::repair(int amount) { durability_ += amount; }
const std::vector<ClassType>& Weapon::allowedClasses() const { return allowedClasses_; }

}
