#include "game_world.h"
#include "economic_growth.h"
#include "population_growth.h"
#include "societal_conditions.h"
#include "military_tactics.h"
#include "event_manager.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // Start the Event Manager thread.
    EventManager::getInstance().start();

    // -------------------------------
    // Economic & Population Simulations
    // -------------------------------
    EconomySimulation economySim(365, 100000, 1000000, 900000);
    PopulationSimulation populationSim(365, 100000, 1000000, 900000);

    economySim.run();
    populationSim.run();

    // Synchronize key values.
    double finalPopulation = populationSim.getCurrentPopulation();
    economySim.updatePopulation(finalPopulation);
    double finalEconomy = economySim.getCurrentEconomy();
    populationSim.updateEconomy(finalEconomy);

    std::cout << "Economic Summary (first 50 days):\n";
    economySim.printSummary(50);
    std::cout << "\nPopulation Summary (first 50 days):\n";
    populationSim.printSummary(50);

    // -------------------------------
    // Game World Setup
    // -------------------------------
    GameWorld world;

    // -------------------------------
    // Update Societal Conditions Daily for Tang Cities
    // -------------------------------
    SocietalConditions societal;
    std::cout << "\nUpdating Societal Conditions for Tang Cities:\n";
    for (int day = 1; day <= 10; ++day) {
        std::cout << "Day " << day << ":\n";
        for (City* city : world.tang.cities) {
            // Update morale and unrest based on other metrics plus random noise.
            societal.updateDaily(*city);
            std::cout << city->cityName << " - Morale: " << city->morale 
                      << ", Unrest: " << city->unrest << "\n";
        }
        std::cout << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // -------------------------------
    // Simulate a Military Attack
    // -------------------------------
    MilitaryTactics tactics;
    // Find the major city "Shanzhou" within Tang.
    City* shanzhou = nullptr;
    for (City* city : world.tang.cities) {
        if (city->cityName == "Shanzhou") {
            shanzhou = city;
            break;
        }
    }
    if (shanzhou) {
        std::cout << "\nSimulating attack on Shanzhou by Tujue:\n";
        // Assume Tujue sends 30,000 troops; use 80 for attacker morale and current city's morale for defenders.
        bool captured = tactics.attackCity(world.tujue, world.tang, *shanzhou, 30000, shanzhou->army_size, 80.0, shanzhou->morale);
        std::cout << "Attack result: " << (captured ? "Shanzhou captured!" : "Shanzhou defended!") << "\n";
    }

    // -------------------------------
    // Test Event Manager with a Sample Event
    // -------------------------------
    EventManager::getInstance().subscribe("TestEvent", [](int value) {
         std::cout << "TestEvent triggered with value: " << value << "\n";
    });
    EventManager::getInstance().queueEvent("TestEvent", 42);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Stop the Event Manager.
    EventManager::getInstance().stop();

    return 0;
}
