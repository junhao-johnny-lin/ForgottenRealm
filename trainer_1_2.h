// FILE: include/Trainer.h
#pragma once
#include "Skills_1_2.h"
#include <vector>
#include <string>

namespace Adventure {

class Trainer {
public:
    Trainer() = default;
    Trainer(std::string name) : name_(std::move(name)) {}

    void addSkill(const Skill& s) { skills_.push_back(s); }
    const std::vector<Skill>& skills() const { return skills_; }
    const std::string& name() const { return name_; }

private:
    std::string name_;
    std::vector<Skill> skills_;
};

} // namespace Adventure
