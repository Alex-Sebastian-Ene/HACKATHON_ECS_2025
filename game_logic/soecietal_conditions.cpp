#include "societal_conditions.h"
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip>

SocietalConditions::SocietalConditions() {
    // Seed the random number generator with current time.
    rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
}

void SocietalConditions::updateDaily(Features &features) {
    // Deterministic factors:
    // 1. Higher happiness tends to raise morale and lower unrest.
    // 2. A popular leader (above 50) boosts morale.
    // 3. High unrest drags morale down.
    // 4. Low morale and low happiness both contribute to increasing unrest.
    // 5. Low food per capita increases unrest.
    double deltaMorale = 0.0;
    double deltaUnrest = 0.0;
    
    // For morale:
    deltaMorale += 0.1 * (features.happiness - 50);            // Happiness effect.
    deltaMorale += 0.05 * (features.leader.popularity - 50);     // Leader popularity effect.
    deltaMorale -= 0.05 * features.unrest;                       // High unrest reduces morale.
    
    // For unrest:
    deltaUnrest += 0.1 * (50 - features.happiness);              // Lower happiness increases unrest.
    deltaUnrest += 0.1 * (50 - features.morale);                 // Lower morale increases unrest.
    
    // Consider food per capita: if food per person is below 1, unrest increases.
    double foodPerCapita = (features.population > 0) ? (static_cast<double>(features.food) / features.population) : 0;
    if (foodPerCapita < 1.0) {
        deltaUnrest += 5.0 * (1.0 - foodPerCapita);
    }
    
    // Random noise components (smaller influence than the deterministic terms):
    std::uniform_real_distribution<double> moraleNoiseDist(-1.0, 1.0);
    std::uniform_real_distribution<double> unrestNoiseDist(-1.0, 1.0);
    deltaMorale += moraleNoiseDist(rng);
    deltaUnrest += unrestNoiseDist(rng);
    
    // Update features while clamping the values to a realistic range (0-100).
    features.morale = std::clamp(static_cast<int>(features.morale + deltaMorale), 0, 100);
    features.unrest = std::clamp(static_cast<int>(features.unrest + deltaUnrest), 0, 100);
}
