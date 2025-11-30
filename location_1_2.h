// FILE: include/Location_1_2.h
#pragma once
#include <string>
#include "Dungeon_1_2.h"
#include "Trainer_1_2.h" // you should have Trainer class; include path must match
#include <optional>

namespace Adventure {

class Location {
public:
    Location();
    Location(std::string id, std::string description, bool hasInn = true, bool hasDungeon = true);

    const std::string& id() const;
    const std::string& description() const;
    bool hasInn() const;
    bool hasDungeon() const;

    Dungeon& dungeon();
    Trainer& trainer();

    void setTrainer(const Trainer& t);
    void setDungeon(const Dungeon& d);

private:
    std::string id_;
    std::string desc_;
    bool hasInn_;
    bool hasDungeon_;
    Dungeon dungeon_;
    Trainer trainer_;
};

} // namespace Adventure
