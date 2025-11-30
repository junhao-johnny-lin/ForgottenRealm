// FILE: include/Item.h
#pragma once
#include "Enums.h"
#include <string>

namespace Adventure {

class Item {
public:
    Item() : id_(0), name_("Unknown"), type_(ItemType::Generic), rarity_(ItemRarity::Common) {}
    Item(int id, std::string name, ItemType t = ItemType::Generic, ItemRarity r = ItemRarity::Common)
        : id_(id), name_(std::move(name)), type_(t), rarity_(r) {}
    virtual ~Item() = default;

    virtual std::string use() = 0; // abstract: implement in derived items

    int id() const { return id_; }
    const std::string& name() const { return name_; }
    ItemType type() const { return type_; }
    ItemRarity rarity() const { return rarity_; }

protected:
    int id_;
    std::string name_;
    ItemType type_;
    ItemRarity rarity_;
};

} // namespace Adventure
