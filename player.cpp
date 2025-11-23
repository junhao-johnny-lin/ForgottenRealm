// player.cpp (toevoeging / vervanging relevante delen)
#include "player.h"
#include <algorithm>

WeaponInstance* PlayerState::getEquippedWeapon() {
    if (equippedWeaponIndex < 0 || equippedWeaponIndex >= (int)weapons.size()) return nullptr;
    return &weapons[equippedWeaponIndex];
}

void PlayerState::removeWeaponAtIndex(int idx) {
    if (idx < 0 || idx >= (int)weapons.size()) return;
    weapons.erase(weapons.begin() + idx);
    if (equippedWeaponIndex == idx) equippedWeaponIndex = -1;
    else if (equippedWeaponIndex > idx) --equippedWeaponIndex;
}

void PlayerState::repairEquippedWeapon(int amount) {
    WeaponInstance* w = getEquippedWeapon();
    if (!w) return;
    int maxd = baseDurabilityForTier(w->tier);
    w->durability = std::min(maxd, w->durability + amount);
}
