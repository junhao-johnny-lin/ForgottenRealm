// map_renderer.h
#pragma once
#include <string>
#include <vector>

struct MapTile {
    char glyph = ' ';
    std::string locationKey;
};

class MapRenderer {
public:
    MapRenderer() = default;
    ~MapRenderer() = default;

    void setMapSize(int width, int height);
    void setHeroLocation(const std::string& locationKey);
    void setAccessibleLocations(const std::vector<std::string>& keys);

    std::vector<std::string> render() const;
};
