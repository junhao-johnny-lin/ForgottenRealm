// FILE: include/Trainer.h
#pragma once
#include "Skills_1_2.h"
#include <vector>
#include <string>

namespace Adventure {

class Trainer {
public:
    Trainer() = default;
    explicit Trainer(std::string name);
    void addSkill(const Skill& s);
    const std::vector<Skill>& skills() const;
    const std::string& name() const;

private:
    std::string name_;
    std::vector<Skill> skills_;
};

} // namespace Adventure
