#pragma once
#include "Entity.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Skills_1_2.h"
#include "Enums.h"
#include <vector>
#include <map>
#include <memory>
#include <string>

namespace Adventure {

class Player : public Entity {
public:
    Player();
    Player(std::string name, ClassType startClass);
    Player(const Player& other);
    ~Player() override;

    void update() override {}

    // basic info
    const std::string& name() const;

    // stats
    int hp() const;
    int maxHp() const;
    int atk() const;
    int def() const;
    int level() const;
    int exp() const;
    int nextLevelExp() const;

    // class progression
    ClassType baseClass() const;
    ClassType advancedClass() const;
    ClassType ultimateClass() const;
    ClassType hiddenClass() const;

    void unlockAdvanced(ClassType c);
    void unlockUltimate(ClassType c);
    void unlockHidden(ClassType c);

    // save/load helpers (used by SaveSystem)
    void overrideName(const std::string& nm);
    void overrideLevel(int lvl);
    void overrideExp(int xp);
    void overrideHp(int hp, int maxHp);
    void overrideBaseClass(ClassType c);

    // combat
    void takeDamage(int dmg);
    void heal(int amount);
    bool isAlive() const;

    // leveling
    void gainExp(int amount);
    void levelUp();

    // inventory
    void addItem(std::shared_ptr<Item> it);
    const std::vector<std::shared_ptr<Item>>& inventory() const;

    bool canEquip(const Item& it) const;
    void equipWeapon(std::shared_ptr<Weapon> w);
    void equipArmor(std::shared_ptr<Armor> a);
    Weapon* weapon() const;
    Armor* armor() const;

    // skills
    bool learnSkill(const Skill& s);
    bool hasSkill(const std::string& id) const;
    const std::map<std::string, Skill>& learnedSkills() const;
    void forceLearnSkill(const std::string& id, int lvl);

    // skill points
    int skillPoints() const;
    void setSkillPoints(int sp);
    void addSkillPoints(int sp);
    bool consumeSkillPoints(int sp);

    // day
    int day() const;
    void setDay(int d);

    // apply achievement rewards (simple hook)
    void applyAchievementBonus(const Skill& bonusSkill);

private:
    std::string name_;
    int hp_, maxHp_;
    int baseAtk_, baseDef_;
    int level_, exp_;
    int skillPoints_;
    int days_;

    ClassType baseClass_;
    ClassType advClass_;
    ClassType ultClass_;
    ClassType hidClass_;

    std::shared_ptr<Weapon> weapon_;
    std::shared_ptr<Armor> armor_;
    std::vector<std::shared_ptr<Item>> inventory_;

    // skills learned by id
    std::map<std::string, Skill> learnedSkills_;
};

} // namespace Adventure
