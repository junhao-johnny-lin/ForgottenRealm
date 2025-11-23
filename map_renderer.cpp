// map_renderer.cpp
#include "map_renderer.h"
#include <algorithm>
#include <string>
#include <vector>

struct Impl {
    int width = 0;
    int height = 0;
    std::string heroLocation;
    std::vector<std::string> accessible;
};

static Impl g_impl;

void MapRenderer::setMapSize(int width, int height) {
    g_impl.width = width; g_impl.height = height;
}

void MapRenderer::setHeroLocation(const std::string& locationKey) {
    g_impl.heroLocation = locationKey;
}

void MapRenderer::setAccessibleLocations(const std::vector<std::string>& keys) {
    g_impl.accessible = keys;
}

std::vector<std::string> MapRenderer::render() const {
    std::vector<std::string> out;
    out.reserve(g_impl.height);
    for (int y = 0; y < g_impl.height; ++y) {
        std::string row;
        for (int x = 0; x < g_impl.width; ++x) row.push_back('.');
        out.push_back(row);
    }
    // simple marker for hero (not location aware)
    if (!out.empty() && !out[0].empty()) out[0][0] = '@';
    return out;
}
