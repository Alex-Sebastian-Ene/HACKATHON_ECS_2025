#ifndef POPULATION_GROWTH_H
#define POPULATION_GROWTH_H

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

struct PopulationData {
    int day;
    double population;
    double militaryPower;
    double economy;
    double warIntensity;
    double netMigrationRate;
};

class PopulationSimulation {
public:
    PopulationSimulation(int days, double P0, double K, double food_supply);
    void run();
    void printSummary(int numDays);
    void updateEconomy(double newEconomy);
    double getCurrentPopulation() const;

private:
    int days;
    double P, K, food_supply, E;
    double warIntensity;
    std::vector<PopulationData> history;
    std::mt19937 rng;
    
    double birth_rate_daily;
    double death_rate_base_daily;
    double alpha;
    double beta;
    double gamma;
    double m0;
    double lambda_migration;
    double econ_sensitivity;
    double p_war;
    int war_duration;
    int war_timer;
    double p_random;
    double random_impact;
    
    double randomDouble();
};

#endif // POPULATION_GROWTH_H