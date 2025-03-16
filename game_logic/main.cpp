#include "game_world.h"
#include "economic_growth.h"      // Make sure updateEconomy() is public!
#include "population_growth.h"
#include "military_tactics.h"
#include "societal_conditions.h"

// Enemy aggression helper (defined in enemy_attack.cpp)
void checkEnemyAggression(Country &enemy, Country &tang);

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

void printTangCities(const Country &tang) {
    std::cout << "Current Tang Cities:\n";
    for (City* city : tang.cities) {
        std::cout << " - " << city->cityName 
                  << " | Population: " << city->population 
                  << " | Money: " << city->money
                  << " | Rebellious: " << (city->isRebelling ? "YES" : "NO") 
                  << "\n";
    }
    std::cout << "-----------------------------------\n";
}

int main() {
    // Seed rand() for any functions that use it.
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize the game world.
    GameWorld world;

    // For simplicity, use the first city of each country as the "capital".
    City* capitalTang = world.tang.cities[0];
    City* capitalTujue = world.tujue.cities[0];
    City* capitalTubo = world.tubo.cities[0];

    // Set initial metrics for each capital.
    capitalTang->money = 5000;
    capitalTang->population = 200000;
    capitalTang->military_experience = 100;

    capitalTujue->money = 5000;
    capitalTujue->population = 200000;
    capitalTujue->military_experience = 100;

    capitalTubo->money = 5000;
    capitalTubo->population = 200000;
    capitalTubo->military_experience = 100;

    // Create simulation objects for Tang.
    // (Parameters: days, starting money/population, carrying capacity, food supply)
    EconomySimulation econSimTang(365, capitalTang->money, 1000000, 900000);
    PopulationSimulation popSimTang(365, capitalTang->population, 1000000, 900000);

    MilitaryTactics tactics;
    SocietalConditions societal;

    std::ofstream outFile("simulation_data.csv");
    outFile << "day,tang_capital_money,tang_capital_population,tang_capital_military_experience\n";

    // Main daily update loop.
    for (int day = 1; day <= 10; ++day) {
        std::cout << "========================\n";
        std::cout << "Day " << day << " update:\n";

        // Update economic and population simulations for Tang.
        econSimTang.updateEconomy();
        popSimTang.run();

        // For demonstration, simulate small daily increments for the capital.
        capitalTang->money += 15;
        capitalTang->population += 8;
        capitalTang->military_experience += 9;

        // Update societal conditions and check for rebellion in each Tang city.
        for (City* city : world.tang.cities) {
            societal.updateDaily(*city);
            if (!city->isRebelling && city->checkRebellion()) {
                city->isRebelling = true;
                // A city wages war on Tang by attacking another random city.
                city->wageWarOnPlayer(world.tang);
            }
        }

        // Check if enemy countries decide to attack Tang.
        checkEnemyAggression(world.tujue, world.tang);
        checkEnemyAggression(world.tubo, world.tang);

        // Distribute the country's economic outcome among Tang's cities.
        double totalPopulation = 0;
        for (City* city : world.tang.cities)
            totalPopulation += city->population;
        double economyShare = econSimTang.getCurrentEconomy() * 0.001; // scaling factor, adjust as needed.
        for (City* city : world.tang.cities) {
            double share = (totalPopulation > 0) ? (static_cast<double>(city->population) / totalPopulation) : 0;
            city->money += economyShare * share;
        }

        // Log current metrics for Tang's capital.
        outFile << day << "," << capitalTang->money << "," 
                << capitalTang->population << "," 
                << capitalTang->military_experience << "\n";

        // Display capital metrics.
        std::cout << "Day " << day << " - Tang Capital Metrics:\n"
                  << "  Money: " << capitalTang->money << "\n"
                  << "  Population: " << capitalTang->population << "\n"
                  << "  Military Exp: " << capitalTang->military_experience << "\n";

        // Also print the current list of Tang cities.
        printTangCities(world.tang);
    }

    outFile.close();
    std::cout << "Simulation complete. Data written to simulation_data.csv\n";
    return 0;
}
