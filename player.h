// player.h
#pragma once
#include "items.h"
#include "loot.h"     // Potion definition
#include <string>
#include <vector>

struct Achievement;

class PlayerState {
public:
    PlayerState();

    // identity / meta
    std::string classId;
    std::string currentLocationKey;

    // inventory
    std::vector<WeaponInstance> weapons; // instances, geen pointers
    std::vector<Potion> potions;

    // equipped
    int equippedWeaponIndex = -1;

    // actions
    void addXp(int amount);
    void repairEquippedWeapon(int amount);

    // helpers
    WeaponInstance* getEquippedWeapon(); // nullptr als geen equipped
    void removeWeaponAtIndex(int idx);

private:
    int hp_;
    int level_;
    int maxHp_;
    int skillPoints_;
    int xp_;
    int attack_;
    int defence_;
};
