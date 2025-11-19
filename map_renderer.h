#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct Location {
    std::string key;
    std::string label; // exact tekst in template
    bool explored = true;
    bool defeated = false;
    bool current = false;
    std::string description;
    int enemiesNearby = 0;
};

void printFullMapWithMarkers(const std::unordered_map<std::string, Location>& nodes,
                             const std::vector<std::string>& tpl,
                             bool showUnexplored = true);

// Gekleurde variant
void printFullMapWithMarkersColored(const std::unordered_map<std::string, Location>& nodes,
                                    const std::vector<std::string>& tpl,
                                    bool showUnexplored = true);

std::vector<std::string> validateTemplateAgainstNodes(const std::vector<std::string>& tpl,
                                                      const std::unordered_map<std::string, Location>& nodes);

const std::vector<std::string>& getTemplateLines();
std::unordered_map<std::string, Location> getDefaultNodesCopy(); // modifiable copy
