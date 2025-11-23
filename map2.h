// map2.h
#pragma once
#include <string>
#include <vector>

struct MapNode {
    std::string key;
    std::string label;
    int x = 0;
    int y = 0;
};

struct GameMap {
    std::string name;
    int width = 0;
    int height = 0;
    std::vector<MapNode> nodes;
    std::string heroLocationKey;
};

GameMap loadDefaultMap();
