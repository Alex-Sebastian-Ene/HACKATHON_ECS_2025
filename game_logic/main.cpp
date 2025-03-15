#include "game_class.h"
#include "event_manager.h"
#include "economic_growth.h"
#include "population_growth.h"
#include "militaryexperience.h"
#include <thread>
#include <chrono>

int main() {
    // Start the Event Manager thread.
    EventManager::getInstance().start();

    // -------------------------------
    // Simulation: Economic & Population
    // -------------------------------
    // Create simulation objects (simulate 365 days)
        EconomySimulation economySim(365, 100000, 1000000, 900000);
        PopulationSimulation populationSim(365, 100000, 1000000, 900000);
    
    // Run both simulations.
    economySim.run();
    populationSim.run();
    
    // Synchronize key variables between the simulations.
    double finalPopulation = populationSim.getCurrentPopulation();
    economySim.updatePopulation(finalPopulation);
    double finalEconomy = economySim.getCurrentEconomy();
    populationSim.updateEconomy(finalEconomy);
    
    // Output summaries (first 50 days).
    std::cout << "Economic Summary:\n";
    economySim.printSummary(50);
    std::cout << "\nPopulation Summary:\n";
    populationSim.printSummary(50);
    
    // -------------------------------
    // Testing Military Strength Module
    // -------------------------------
    MilitaryStrength milStr;
    // Set some test values.
    milStr.last_day_since_war = 15;
    milStr.wars_fought = 5;
    milStr.wars_won = 3;
    milStr.wars_lost = 2;
    milStr.military_experience = 50;
    milStr.military_power = 200;
    milStr.military_technology = 30;
    
    std::cout << "\nMilitary Strength Summary:\n";
    milStr.printSummary();
    std::cout << "Calculated Readiness: " << milStr.calculateReadiness() << "\n";
    
    // -------------------------------
    // Testing Game Simulation
    // -------------------------------
    Game game;
    
    // Create two factions with leaders.
    Group faction1("Red Faction");
    faction1.addLeader(new MilitaryLeader("General Red", 20, 15, 100, 25, 30));
    faction1.addLeader(new EconomicLeader("Trader Red", 15, 10, 80, 20, 25));
    
    Group faction2("Blue Faction");
    faction2.addLeader(new ResearchLeader("Scientist Blue", 10, 12, 70, 40, 35));
    faction2.addLeader(new PoliticalLeader("Diplomat Blue", 18, 14, 90, 30, 20));
    
    // Add factions to the game.
    game.addFaction(faction1);
    game.addFaction(faction2);
    
    // Start the game simulation.
    std::cout << "\nGame Simulation:\n";
    game.startGame();
    
    // -------------------------------
    // Testing Event Manager - Simple Event
    // -------------------------------
    // Subscribe to a test event.
    EventManager::getInstance().subscribe("TestEvent", [](int value){
         std::cout << "TestEvent triggered with value: " << value << "\n";
    });
    
    // Queue an event.
    EventManager::getInstance().queueEvent("TestEvent", 42);
    
    // Give a brief pause for event processing.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Stop the Event Manager.
    EventManager::getInstance().stop();
    
    return 0;
}
