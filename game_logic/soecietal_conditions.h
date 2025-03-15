#ifndef SOCIETAL_CONDITIONS_H
#define SOCIETAL_CONDITIONS_H

#include <random>
#include "game_class.h"  // For Features

class SocietalConditions {
public:
    SocietalConditions();

    // Update daily morale and unrest for the given Features instance.
    void updateDaily(Features &features);

private:
    std::mt19937 rng;
};

#endif // SOCIETAL_CONDITIONS_H
