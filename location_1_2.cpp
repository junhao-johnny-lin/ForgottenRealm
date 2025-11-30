// FILE: src/Location_1_2.cpp
#include "Location_1_2.h"

namespace Adventure {

Location::Location() : id_("Unknown"), desc_(""), hasInn_(true), hasDungeon_(true) {}
Location::Location(std::string id, std::string description, bool hasInn, bool hasDungeon)
    : id_(std::move(id)), desc_(std::move(description)), hasInn_(hasInn), hasDungeon_(hasDungeon) {}

const std::string& Location::id() const { return id_; }
const std::string& Location::description() const { return desc_; }
bool Location::hasInn() const { return hasInn_; }
bool Location::hasDungeon() const { return hasDungeon_; }

Dungeon& Location::dungeon() { return dungeon_; }
Trainer& Location::trainer() { return trainer_; }

void Location::setTrainer(const Trainer& t) { trainer_ = t; }
void Location::setDungeon(const Dungeon& d) { dungeon_ = d; }

} // namespace Adventure
