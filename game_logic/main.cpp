#include "game_class.h"
#include "event_manager.h"

int main() {
    EventManager::getInstance().start();

    Game tangDynastyGame;

    // Create factions
    Group tangEmpire("Tang Empire", 50000, 70);
    Group rebels("Rebel Faction", 15000, 50);

    // Create leaders
    MilitaryLeader* general = new MilitaryLeader("Li Jing", 15, 85, 70, 90, 80);
    PoliticalLeader* chancellor = new PoliticalLeader("Wei Zheng", 18, 80, 75, 88, 92);

    // Add leaders
    tangEmpire.addLeader(general);
    rebels.addLeader(chancellor);

    // Add factions to the game
    tangDynastyGame.addFaction(tangEmpire);
    tangDynastyGame.addFaction(rebels);

    // Subscribe to events
    EventManager::getInstance().subscribe("GameStarted", [](int) {
        std::cout << "🛡️ The Tang Dynasty begins its journey...\n";
    });

    EventManager::getInstance().subscribe("WarStarted", [](int) {
        std::cout << "🔥 War has begun! Troops are mobilizing!\n";
    });

    // Start the game
    tangDynastyGame.startGame();

    // Simulate war
    EventManager::getInstance().queueEvent("WarStarted", 1);

    // Clean up
    delete general;
    delete chancellor;

    EventManager::getInstance().stop();

    return 0;
}
