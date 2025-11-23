// trainer.cpp
#include "trainer.h"
#include <algorithm>

std::vector<TrainerOffer> getDefaultTrainerOffers() {
    std::vector<TrainerOffer> v = {
                                   {"t_evade", "Learn Evade", 1, "evade"},
                                   {"t_fireball", "Train Fireball", 2, "fireball"},
                                   {"t_strike", "Improve Strike", 0, "strike"},
                                   };
    std::sort(v.begin(), v.end(), [](const TrainerOffer& a, const TrainerOffer& b){ return a.id < b.id; });
    return v;
}
