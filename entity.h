// FILE: include/Entity.h
#pragma once
#include <string>

namespace Adventure {

class Entity {
public:
    Entity() = default;
    explicit Entity(std::string name) : name_(std::move(name)) {}
    virtual ~Entity() = default;

    virtual void update() = 0;
    const std::string& name() const { return name_; }

protected:
    std::string name_;
};

} // namespace Adventure
