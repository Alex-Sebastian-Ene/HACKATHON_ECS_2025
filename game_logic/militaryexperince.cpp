#include "militaryexperience.h"

MilitaryStrength::MilitaryStrength()
    : last_day_since_war(0), wars_won(0), wars_lost(0), wars_fought(0),
      military_experience(0), military_power(0), military_technology(0) {}

MilitaryStrength::MilitaryStrength(int lastDay, int won, int lost, int fought,
                                   int experience, int power, int technology)
    : last_day_since_war(lastDay), wars_won(won), wars_lost(lost), wars_fought(fought),
      military_experience(experience), military_power(power), military_technology(technology) {}

void MilitaryStrength::printSummary() const {
    std::cout << "===== Military Strength Summary =====\n";
    std::cout << "Last day since war: " << last_day_since_war << "\n";
    std::cout << "Wars fought:        " << wars_fought << "\n";
    std::cout << "Wars won:           " << wars_won << "\n";
    std::cout << "Wars lost:          " << wars_lost << "\n";
    std::cout << "Military experience:" << military_experience << "\n";
    std::cout << "Military power:     " << military_power << "\n";
    std::cout << "Military technology:" << military_technology << "\n";
    std::cout << "=====================================\n";
}

double MilitaryStrength::calculateReadiness() const {
    // Define weights for different military metrics.
    const double weightExperience   = 1.0;
    const double weightPower        = 0.5;
    const double weightTechnology   = 0.7;
    const double weightCampaign     = 10.0; // Reward for wins, penalty for losses

    // Base readiness factors: experience, power, technology, and campaign results.
    double baseReadiness = (military_experience * weightExperience +
                            military_power * weightPower +
                            military_technology * weightTechnology +
                            wars_won * weightCampaign -
                            wars_lost * (weightCampaign / 2.0));


    double fatigueFactor = 1.0;
    const int fatigueThreshold = 30; // Recovery period in days
    if (last_day_since_war < fatigueThreshold) {
        fatigueFactor = static_cast<double>(last_day_since_war) / fatigueThreshold;
    }

    // Final readiness is the base readiness adjusted by the fatigue factor.
    double readiness = baseReadiness * fatigueFactor;
    return readiness;
}
