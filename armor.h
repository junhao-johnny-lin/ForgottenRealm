#pragma once
#include "Item.h"
#include "Enums.h"
#include <string>
#include <vector>

namespace Adventure {

class Armor : public Item {
public:
    Armor();
    Armor(int id, std::string name, int def, int dur, ItemRarity r, std::vector<ClassType> allowed);

    // ➕ ADD THIS (needed for save/load)
    Armor(std::string name, int def, ItemRarity r);

    Armor(const Armor& other);
    ~Armor() override;

    std::string use() override;
    int defense() const;
    int durability() const;
    void takeHit(int amount);
    const std::vector<ClassType>& allowedClasses() const;

private:
    int defense_;
    int durability_;
    std::vector<ClassType> allowedClasses_;
};

} // namespace Adventure
