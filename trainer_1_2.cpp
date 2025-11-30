// FILE: src/Trainer.cpp
#include "Trainer_1_2.h"

namespace Adventure {

Trainer::Trainer(std::string name) : name_(std::move(name)) {}
void Trainer::addSkill(const Skill& s) { skills_.push_back(s); }
const std::vector<Skill>& Trainer::skills() const { return skills_; }
const std::string& Trainer::name() const { return name_; }

} // namespace Adventure
