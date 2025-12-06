#include "Armor.h"

namespace Adventure {

Armor::Armor()
    : Item(0, "Unnamed Armor", ItemRarity::Common),
      defense_(1), durability_(100) {}

Armor::Armor(int id, std::string name, int def, int dur, ItemRarity r, std::vector<ClassType> allowed)
    : Item(id, name, r),
      defense_(def), durability_(dur),
      allowedClasses_(std::move(allowed)) {}

// ➕ ADD THIS (used by SaveSystem)
Armor::Armor(std::string name, int def, ItemRarity r)
    : Item(0, name, r),
      defense_(def),
      durability_(100),
      allowedClasses_({})
{}

Armor::Armor(const Armor& other) = default;
Armor::~Armor() = default;

std::string Armor::use() { return "Clink!"; }
int Armor::defense() const { return defense_; }
int Armor::durability() const { return durability_; }
void Armor::takeHit(int amount) { durability_ -= amount; }
const std::vector<ClassType>& Armor::allowedClasses() const { return allowedClasses_; }

}
