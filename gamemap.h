// FILE: include/GameMap.h
#pragma once
#include "Location_1_2.h"
#include <vector>
#include <string>

namespace Adventure {

class GameMap {
public:
    GameMap();
    const std::vector<Location>& locations() const;
    const Location* getLocationById(const std::string& id) const;
    Location* getLocationById(const std::string& id);
    void draw() const;

private:
    void build();
    std::vector<Location> locations_;
};

} // namespace Adventure
