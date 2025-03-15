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
    // Stabilized morale: instead of strictly rising/falling, it tends toward a natural equilibrium
    double deltaMorale = 0.0;
    double deltaUnrest = 0.0;

    // --- Morale Adjustments ---
    const double baseMorale = 60.0;  // Morale tends to remain near this baseline.
    double moraleDeviation = features.morale - baseMorale;

    // The further morale is from the baseline, the slower it shifts
    deltaMorale -= 0.05 * moraleDeviation; // Pulls morale toward equilibrium

    // Happiness and leadership influence
    deltaMorale += 0.08 * (features.happiness - 50);
    deltaMorale += 0.04 * (features.leader.popularity - 50);

    // Unrest reduces morale but in a non-strict way
    deltaMorale -= 0.02 * features.unrest;

    // --- Unrest Adjustments ---
    deltaUnrest += 0.08 * (50 - features.happiness); // Unhappiness increases unrest
    deltaUnrest += 0.05 * (50 - features.morale);    // Low morale increases unrest
    deltaUnrest -= 0.02 * features.leader.popularity; // Popular leaders calm unrest

    // Food scarcity still plays a key role
    double foodPerCapita = (features.population > 0) ? (static_cast<double>(features.food) / features.population) : 0;
    if (foodPerCapita < 1.0) {
        deltaUnrest += 4.0 * (1.0 - foodPerCapita);
    }

    // --- Larger Fluctuations ---
    // Random morale swings are now more impactful when unrest is high.
    std::uniform_real_distribution<double> moraleNoiseDist(-2.0, 2.0); // Larger range than before
    std::uniform_real_distribution<double> unrestNoiseDist(-1.5, 1.5);
    
    // Dynamic noise scaling: if unrest is high, random fluctuations increase
    double noiseScaling = 1.0 + (features.unrest / 50.0);
    deltaMorale += moraleNoiseDist(rng) * noiseScaling;
    deltaUnrest += unrestNoiseDist(rng) * noiseScaling;

    // --- Placeholder for City Influence (To Be Expanded) ---
    // Idea: Nearby cities influence morale through communication and rumors.
    // Example: If nearby city unrest is high, this city also gets unrest pressure.
    // For now, it's left as a conceptual part.
    // TODO: Implement cross-city morale impact

    // --- Final Updates ---
    features.morale = std::clamp(static_cast<int>(features.morale + deltaMorale), 0, 100);
    features.unrest = std::clamp(static_cast<int>(features.unrest + deltaUnrest), 0, 100);
}
