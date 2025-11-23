// FILE: src/Location.cpp
#include "location_1_2.h"
#include "Trainer_1_2.h"


namespace Adventure {

Location::Location(std::string id, std::string desc) : id_(std::move(id)), desc_(std::move(desc)) {}
void Location::addEnemy(const Enemy& e) { enemies_.push_back(e); }
void Location::setTrainer(Trainer t) { trainer_ = std::move(t); hasTrainer_ = true; }
const std::string& Location::id() const { return id_; }
const std::string& Location::desc() const { return desc_; }
bool Location::hasDungeon() const { return hasDungeon_; }
void Location::setDungeon(bool v) { hasDungeon_ = v; }
bool Location::hasInn() const { return hasInn_; }
void Location::setInn(bool v) { hasInn_ = v; }
bool Location::hasTrainer() const { return hasTrainer_; }
Trainer* Location::trainer() { return hasTrainer_ ? &trainer_ : nullptr; }
const std::vector<Enemy>& Location::enemies() const { return enemies_; }
void Location::addAchievementId(const std::string& id) { achievementIds_.push_back(id); }
const std::vector<std::string>& Location::achievementIds() const { return achievementIds_; }

} // namespace Adventure

