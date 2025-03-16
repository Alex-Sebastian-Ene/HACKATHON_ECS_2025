#include "military_tactics.h"
#include "game_world.h"
#include <cstdlib>  // For rand()

// Helper function to check if an enemy country should attack Tang.
void checkEnemyAggression(Country &enemy, Country &tang) {
    // Assume enemy has one city.
    if (!enemy.cities.empty() && enemy.cities[0]->happiness > 80) {
        std::cout << enemy.countryName << " is feeling exceptionally happy and decides to wage war on Tang!\n";
        MilitaryTactics tactics;
        // Choose a random Tang city to attack.
        if (!tang.cities.empty()) {
            int idx = rand() % tang.cities.size();
            City* targetCity = tang.cities[idx];
            std::cout << enemy.countryName << " launches an attack on " << targetCity->cityName << "!\n";
            bool success = tactics.attackCity(enemy, tang, *targetCity,
                                              enemy.cities[0]->army_size, targetCity->army_size,
                                              enemy.cities[0]->morale, targetCity->morale);
            if (success) {
                std::cout << enemy.countryName << " has captured " << targetCity->cityName << "!\n";
                // Mark the captured Tang city as rebellious.
                targetCity->isRebelling = true;
            } else {
                std::cout << enemy.countryName << "'s attack on " << targetCity->cityName << " failed.\n";
            }
        }
    }
}