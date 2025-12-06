#pragma once
#include "Item.h"
#include "Enums.h"
#include <string>
#include <vector>

namespace Adventure {

class Weapon : public Item {
public:
    Weapon();
    Weapon(int id, std::string name, int dmg, int dur, ItemRarity r, std::vector<ClassType> allowed);

    // ➕ ADD THIS CONSTRUCTOR (needed for save/load)
    Weapon(std::string name, int dmg, ItemRarity r);

    Weapon(const Weapon& other);
    ~Weapon() override;

    std::string use() override;
    int damage() const;
    int durability() const;
    void repair(int amount);
    const std::vector<ClassType>& allowedClasses() const;

private:
    int damage_;
    int durability_;
    std::vector<ClassType> allowedClasses_;
};

} // namespace Adventure
