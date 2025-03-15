#ifndef ECONOMIC_GROWTH_H
#define ECONOMIC_GROWTH_H

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>

struct EconomicData {
    int day;
    double population;
    double militaryPower;
    double money;
    double technology;
    double happiness;
    double warIntensity;
    double netMigrationRate;
};

class EconomySimulation {
public:
    EconomySimulation(int days, double P0, double K, double food_supply);
    void run();
    void printSummary(int numDays);
    void updatePopulation(double newPopulation);
    double getCurrentEconomy() const;

private:
    double foodProduction, woodProduction, stoneProduction, metalProduction;
    double consumptionRate, taxRate, productionTaxRate, expenditureRate;
    double exportPrice, importPrice;
    int days;
    double P, K, food_supply, money, technology, happiness;
    double warIntensity;
    std::vector<EconomicData> history;
    std::mt19937 rng;
    double randomDouble();
    void updateEconomy();
};

#endif // ECONOMIC_GROWTH_H
