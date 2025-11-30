// FILE: gamemap.h
#pragma once
#include "location_1_2.h"
#include <vector>
#include <string>

namespace Adventure {

class GameMap {
public:
    GameMap();

    void draw() const;

    const std::vector<Location>& locations() const;
    Location* getLocation(const std::string& id);

private:
    void build();

    // DIT MOET EEN VECTOR ZIJN, NIET EEN POINTER!
    std::vector<Location> locations_;
};

} // namespace Adventure
