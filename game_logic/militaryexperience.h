#ifndef MILITARY_STRENGTH_H
#define MILITARY_STRENGTH_H

#include <iostream>

class MilitaryStrength {
public:
    int last_day_since_war;
    int wars_won;
    int wars_lost;
    int wars_fought;
    int military_experience;
    int military_power;
    int military_technology;

    // Constructors
    MilitaryStrength();
    MilitaryStrength(int lastDay, int won, int lost, int fought,
                     int experience, int power, int technology);

    // Outputs a formatted summary of the military metrics
    void printSummary() const;

    // Calculates a readiness metric based on campaigns and recent war fatigue
    double calculateReadiness() const;
};

#endif // MILITARY_STRENGTH_H
