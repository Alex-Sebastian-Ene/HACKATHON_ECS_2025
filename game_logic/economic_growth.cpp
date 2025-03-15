#include "economic_growth.h"

EconomySimulation::EconomySimulation(int days, double P0, double K, double food_supply)
    : days(days), P(P0), K(K), food_supply(food_supply),
      money(5000), technology(5), happiness(50),
      warIntensity(0.0),
      rng(std::chrono::steady_clock::now().time_since_epoch().count()),
      // Initialization of production values
      foodProduction(300.0), woodProduction(200.0), stoneProduction(200.0), metalProduction(20.0),
      // Initialization of rates
      consumptionRate(0.01), taxRate(0.025), productionTaxRate(0.002), expenditureRate(0.003),
      // Initialization of trade prices
      exportPrice(2.0), importPrice(1.5)
{
}

void EconomySimulation::run() {
    for (int day = 1; day <= days; ++day) {
        updateEconomy();

        EconomicData data;
        data.day = day;
        data.population = P;
        data.militaryPower = 0.4 * P;
        data.money = money;
        data.technology = technology;
        data.happiness = happiness;
        data.warIntensity = warIntensity;
        data.netMigrationRate = 0.0;

        history.push_back(data);
    }
}

void EconomySimulation::printSummary(int numDays) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(5)  << "Day"
              << std::setw(12) << "Population"
              << std::setw(12) << "Mil.Power"
              << std::setw(10) << "Money"
              << std::setw(8)  << "Tech"
              << std::setw(12) << "Happiness"
              << std::setw(12) << "WarInten"
              << std::setw(10) << "NetMig"
              << "\n";

    for (size_t i = 0; i < history.size() && i < static_cast<size_t>(numDays); ++i) {
        const auto& d = history[i];
        std::cout << std::setw(5)  << d.day
                  << std::setw(12) << d.population
                  << std::setw(12) << d.militaryPower
                  << std::setw(10) << d.money
                  << std::setw(8)  << d.technology
                  << std::setw(12) << d.happiness
                  << std::setw(12) << d.warIntensity
                  << std::setw(10) << d.netMigrationRate
                  << "\n";
    }
}

void EconomySimulation::updatePopulation(double newPopulation) {
    P = newPopulation;
}

double EconomySimulation::getCurrentEconomy() const {
    return money;
}

double EconomySimulation::randomDouble() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}

void EconomySimulation::updateEconomy() {
    // Compute production adjusted by technology (capped at 100)
    double cappedTech = std::min(technology, 100.0);
    double techMultiplier = 1.0 + (cappedTech / 100.0);
    double totalProduction = (foodProduction + woodProduction + stoneProduction + metalProduction) * techMultiplier;
    double totalConsumption = P * consumptionRate * 2.0;
    
    // Trade income: if production falls short, we incur import costs.
    double exportIncome = std::max(0.0, (totalProduction - totalConsumption) * exportPrice);
    double importCost = std::max(0.0, (totalConsumption - totalProduction) * importPrice);
    double tradeIncome = exportIncome - importCost;
    
    // Tax revenue and expenditures
    double taxRevenue = P * taxRate + totalProduction * productionTaxRate;
    double expenditures = P * expenditureRate;
    
    // Calculate net income from this cycle
    double netIncome = taxRevenue + tradeIncome - expenditures;
    
    // Update technology slowly if net income is positive (damped) and cap at 100
    if (netIncome > 0)
        technology = std::min(technology + netIncome * 0.0025, 100.0);
    
    // Use a stronger damping factor on net income to reduce explosive growth.
    double dampedIncome = netIncome * 0.1;
    
    // Calculate a modest inflation rate (only when net income is positive) with reduced sensitivity.
    double inflationRate = (netIncome > 0 ? netIncome * 0.1 : 0.0) / 1000000.0;
    
    // Update money with the damped net income
    money += dampedIncome;
    
    // Apply inflation effect: reduce purchasing power
    money *= (1.0 - inflationRate);
    
    // Clamp money so it never falls below -10000 (max debt)
    if (money < -10000)
        money = -10000;
    
    // Slightly adjust trade prices to reflect inflation
    exportPrice *= (1.0 + inflationRate);
    importPrice *= (1.0 + inflationRate);
    
    // Update happiness with a very mild effect (damped)
    happiness = std::clamp(happiness + netIncome * 0.001 - warIntensity * 2.0, 10.0, 100.0);
}
