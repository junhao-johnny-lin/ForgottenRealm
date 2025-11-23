// trainer.h
#pragma once
#include <string>
#include <vector>

struct TrainerOffer {
    std::string id;
    std::string description;
    int costSkillPoints = 0;
    std::string unlocksSkillId;
};

std::vector<TrainerOffer> getDefaultTrainerOffers();
