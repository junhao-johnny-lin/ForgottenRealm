#include "Player_1_2.h"
#include "Skills_1_2.h"
#include <iostream>

namespace Adventure {

Player::Player()
    : name_("Hero"), hp_(100), maxHp_(100), baseAtk_(5), baseDef_(2),
      level_(1), exp_(0), skillPoints_(0), days_(0),
      baseClass_(ClassType::Knight), advClass_(ClassType::Knight),
      ultClass_(ClassType::Knight), hidClass_(ClassType::Knight),
      weapon_(nullptr), armor_(nullptr)
{}

Player::Player(std::string name, ClassType startClass)
    : name_(std::move(name)), hp_(100), maxHp_(100), baseAtk_(5), baseDef_(2),
      level_(1), exp_(0), skillPoints_(0), days_(0),
      baseClass_(startClass), advClass_(startClass),
      ultClass_(startClass), hidClass_(startClass),
      weapon_(nullptr), armor_(nullptr)
{}

Player::Player(const Player& other) = default;
Player::~Player() = default;

const std::string& Player::name() const { return name_; }

int Player::hp() const { return hp_; }
int Player::maxHp() const { return maxHp_; }
int Player::atk() const { return baseAtk_ + (weapon_ ? weapon_->damage() : 0); }
int Player::def() const { return baseDef_ + (armor_ ? armor_->defense() : 0); }
int Player::level() const { return level_; }
int Player::exp() const { return exp_; }
int Player::nextLevelExp() const { return 50 + level_ * 25; }

ClassType Player::baseClass() const { return baseClass_; }
ClassType Player::advancedClass() const { return advClass_; }
ClassType Player::ultimateClass() const { return ultClass_; }
ClassType Player::hiddenClass() const { return hidClass_; }

void Player::unlockAdvanced(ClassType c) { advClass_ = c; }
void Player::unlockUltimate(ClassType c) { ultClass_ = c; }
void Player::unlockHidden(ClassType c) { hidClass_ = c; }

void Player::overrideName(const std::string& nm) { name_ = nm; }
void Player::overrideLevel(int lvl) { level_ = lvl; }
void Player::overrideExp(int xp) { exp_ = xp; }
void Player::overrideHp(int hp, int maxHp) { hp_ = hp; maxHp_ = maxHp; }
void Player::overrideBaseClass(ClassType c) { baseClass_ = c; advClass_ = c; ultClass_ = c; hidClass_ = c; }

void Player::takeDamage(int dmg) {
    int mitig = def();
    int finalD = dmg - mitig;
    if (finalD < 1) finalD = 1;
    hp_ -= finalD;
    if (hp_ < 0) hp_ = 0;
}

void Player::heal(int amount) {
    hp_ += amount;
    if (hp_ > maxHp_) hp_ = maxHp_;
}

bool Player::isAlive() const { return hp_ > 0; }

void Player::gainExp(int amount) {
    exp_ += amount;
    while (exp_ >= nextLevelExp()) {
        exp_ -= nextLevelExp();
        levelUp();
    }
}

void Player::levelUp() {
    level_++;
    skillPoints_++;
    maxHp_ += 10;
    hp_ = maxHp_;
    baseAtk_ += 1;
    baseDef_ += 1;
    std::cout << "Level up! " << level_ << " (SP +" << 1 << ")\n";
}

void Player::addItem(std::shared_ptr<Item> it) { inventory_.push_back(it); }
const std::vector<std::shared_ptr<Item>>& Player::inventory() const { return inventory_; }

bool Player::canEquip(const Item& it) const {
    if (it.type() == ItemType::Weapon) {
        const Weapon& w = dynamic_cast<const Weapon&>(it);
        const auto& list = w.allowedClasses();
        for (auto c : list) if (c == baseClass_ || c == advClass_ || c == ultClass_ || c == hidClass_) return true;
        return false;
    }
    if (it.type() == ItemType::Armor) {
        const Armor& a = dynamic_cast<const Armor&>(it);
        const auto& list = a.allowedClasses();
        for (auto c : list) if (c == baseClass_ || c == advClass_ || c == ultClass_ || c == hidClass_) return true;
        return false;
    }
    return true;
}

void Player::equipWeapon(std::shared_ptr<Weapon> w) {
    if (!w) return;
    if (!canEquip(*w)) throw std::runtime_error("Cannot equip weapon");
    weapon_ = w;
}
void Player::equipArmor(std::shared_ptr<Armor> a) {
    if (!a) return;
    if (!canEquip(*a)) throw std::runtime_error("Cannot equip armor");
    armor_ = a;
}
Weapon* Player::weapon() const { return weapon_.get(); }
Armor* Player::armor() const { return armor_.get(); }

bool Player::learnSkill(const Skill& s) {
    if (level_ < s.requiredLevel) return false;
    if (skillPoints_ < s.cost) return false;
    learnedSkills_[s.id] = s;
    skillPoints_ -= s.cost;
    return true;
}
bool Player::hasSkill(const std::string& id) const { return learnedSkills_.count(id) != 0; }
const std::map<std::string, Skill>& Player::learnedSkills() const { return learnedSkills_; }
void Player::forceLearnSkill(const std::string& id, int lvl) {
    const Skill* sk = SkillTree::instance().skillById(id);
    if (sk) {
        Skill s = *sk;
        s.requiredLevel = lvl;
        learnedSkills_[id] = s;
    } else {
        Skill s; s.id = id; s.name = id; s.requiredLevel = lvl; s.cost = 0;
        learnedSkills_[id] = s;
    }
}

int Player::skillPoints() const { return skillPoints_; }
void Player::setSkillPoints(int sp) { skillPoints_ = sp; }
void Player::addSkillPoints(int sp) { skillPoints_ += sp; }
bool Player::consumeSkillPoints(int sp) { if (skillPoints_ < sp) return false; skillPoints_ -= sp; return true; }

int Player::day() const { return days_; }
void Player::setDay(int d) { days_ = d; }

void Player::applyAchievementBonus(const Skill& bonusSkill) {
    // Simple implementation: grant the skill if possible; if already present, give 1 skill point
    if (!hasSkill(bonusSkill.id)) {
        learnedSkills_[bonusSkill.id] = bonusSkill;
    } else {
        addSkillPoints(1);
    }
}

} // namespace Adventure
