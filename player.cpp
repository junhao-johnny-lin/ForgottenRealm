#include "player.h"
#include "class_defs.h"
#include "achievements.h"
#include <iostream>
#include <algorithm>

// XP curve
static inline int xpForNextLevel(int level) { return 100 * level; }

// Apply a single achievement's mods to player (safe single-apply)
static void applyAchievementModsToPlayer(PlayerState& player, const Achievement& a) {
    player.permHpBoost += a.mods.hp;
    player.permAttackBoost += a.mods.strength;
    player.permDefenceBoost += a.mods.defence;
    player.maxHp += a.mods.hp;
    if (player.hp > player.maxHp) player.hp = player.maxHp;
}

// Apply all unlocked achievements once. Call this after load or when initializing a new game.
// Note: to avoid double-apply, call only once after load or ensure achievements are fresh.
void applyAchievementsToPlayer(PlayerState& player, const std::vector<Achievement>& achievements) {
    // Reset perm boosts before applying if you want idempotence; here we assume fresh call after load/new game
    // If you need full idempotence without resetting existing perm* fields, adapt to compute difference.
    for (const auto& a : achievements) {
        if (!a.unlocked) continue;
        applyAchievementModsToPlayer(player, a);
    }
}

void applySingleUnlockedAchievementToPlayer(PlayerState& player, const Achievement& a) {
    if (!a.unlocked) return;
    applyAchievementModsToPlayer(player, a);
}

void applyClassStageBonuses(PlayerState& player, int stageIndex) {
    auto& all = getAllClasses();
    auto it = all.find(player.classId);
    if (it == all.end()) return;
    if (stageIndex == 0) { player.attack += 2; player.defence += 1; player.maxHp += 5; }
    else if (stageIndex == 1) { player.attack += 3; player.defence += 2; player.maxHp += 10; }
    else if (stageIndex == 2) { player.attack += 5; player.defence += 3; player.maxHp += 20; }
    if (player.hp > player.maxHp) player.hp = player.maxHp;
    std::cout << "Class stage " << stageIndex << " toegepast.\n";
}

void levelUp(PlayerState& player) {
    bool leveled = false;
    while (player.xp >= xpForNextLevel(player.level)) {
        int need = xpForNextLevel(player.level);
        player.xp -= need;
        player.level += 1;
        player.skillPoints += 2;
        leveled = true;
        std::cout << "Level up! Nu level " << player.level << ". Skill points: " << player.skillPoints << "\n";
        if (player.level == 5) applyClassStageBonuses(player, 0);
        if (player.level == 10) applyClassStageBonuses(player, 1);
        if (player.level == 20) applyClassStageBonuses(player, 2);
        int heal = std::max(1, player.maxHp / 10);
        player.hp = std::min(player.hp + heal, player.maxHp);
        std::cout << "Hersteld " << heal << " HP.\n";
    }
    if (!leveled) {
        int need = xpForNextLevel(player.level) - player.xp;
        std::cout << "XP: " << player.xp << ", nog " << need << " tot level " << (player.level + 1) << "\n";
    }
}
