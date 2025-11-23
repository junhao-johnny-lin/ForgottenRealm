#include "map_renderer.h"
#include <iostream>
#include <iomanip>

// Very simple renderer: list locations and status
void renderMap(const std::unordered_map<std::string, Location>& nodes) {
    std::cout << "\n--- KAART LOCATIES ---\n";
    for (const auto& kv : nodes) {
        const auto& key = kv.first;
        const auto& n = kv.second;
        std::cout << key << " : " << n.label
                  << (n.accessible ? " [A]" : " [ ]")
                  << (n.hasDungeon ? " [D]" : "")
                  << (n.hasInn ? " [Inn]" : "")
                  << (n.hasTrainer ? " [T]" : "")
                  << (n.dungeonCleared ? " [CLEARED]" : "")
                  << "\n";
    }
    std::cout << "----------------------\n";
}
