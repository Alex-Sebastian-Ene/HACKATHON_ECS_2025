// competition_env.cpp
#include "game_world.h"
#include "economic_growth.h"
#include "population_growth.h"
#include "military_tactics.h"
#include "societal_conditions.h"
#include <iostream>
#include <fstream>

int main() {
    GameWorld world;

    City* capitalTang = world.tang.cities[0];
    City* capitalTujue = world.tujue.cities[0];
    City* capitalTubo = world.tubo.cities[0];

    capitalTang->money = 5000;
    capitalTang->population = 200000;
    capitalTang->military_experience = 100;

    capitalTujue->money = 5000;
    capitalTujue->population = 200000;
    capitalTujue->military_experience = 100;

    capitalTubo->money = 5000;
    capitalTubo->population = 200000;
    capitalTubo->military_experience = 100;

    EconomySimulation econSimTang(365, capitalTang->money, 1000000, 900000);
    PopulationSimulation popSimTang(365, capitalTang->population, 1000000, 900000);

    MilitaryTactics tactics;
    SocietalConditions societal;

    std::ofstream outFile("simulation_data.csv");
    outFile << "day,money,population,military_experience\n";

    for (int day = 1; day <= 10; ++day) {
        econSimTang.updateEconomy();
        popSimTang.run();

        capitalTang->money += 50 * 0.3;  
        capitalTang->population += 20 * 0.4; 
        capitalTang->military_experience += 30 * 0.3;

        bool battleResult = tactics.attackCity(
            *world.tujue.cities[0], world.tang, *capitalTang,
            30000, capitalTang->army_size, 80.0, capitalTang->morale
        );

        if (battleResult) {
            capitalTang->military_experience += 10;
        } else {
            capitalTang->military_experience -= 5;
        }

        for (City* city : world.tang.cities) {
            societal.updateDaily(*city);
        }

        outFile << day << "," << capitalTang->money << "," 
                << capitalTang->population << "," 
                << capitalTang->military_experience << "\n";

        std::cout << "Day " << day << " - Tang Metrics: Money: " << capitalTang->money
                  << ", Population: " << capitalTang->population
                  << ", Military Exp: " << capitalTang->military_experience << "\n";
    }

    outFile.close();
    return 0;
}
