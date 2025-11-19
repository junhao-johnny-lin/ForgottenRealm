#pragma once // zorgt ervoor dat de compiler de header 1 keer leest

#include <string>
#include <map>

struct Location {
    std::string name;
    int x;
    int y;
};

class GameMap {
public:
    GameMap();                  // Constructor vult locaties
    void draw() const;          // Tekent de kaart met heldpositie
    void setHeroLocation(const std::string& locName); // Zet held naar een vaste locatie
    void listAvailableLocations() const;

    // Getter voor huidige locatie
    std::string getHeroLocation() const {
        return heroLocationName;
    }

    // Optioneel: reset naar standaardlocatie
    void resetHeroLocation(const std::string& defaultLoc = "Araluen") {
        heroLocationName = defaultLoc;
    }

    // Locaties worden extern gevuld via location.h
    friend void initializeLocations(GameMap& map);

private:
    std::string heroLocationName;
    std::map<std::string, Location> locations; // Bekende locaties met coördinaten
};
