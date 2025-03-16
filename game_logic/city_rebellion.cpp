#include "game_class.h"
#include "military_tactics.h"
#include <cstdlib>
#include <vector>
#include <algorithm>

void City::wageWarOnPlayer(Country &playerCountry) {
    std::cout << cityName << " has rebelled and is now waging war on the player!\n";

    // Build a list of target cities (exclude this city).
    std::vector<City*> potentialTargets;
    for (City* c : playerCountry.cities) {
        if (c != this) {
            potentialTargets.push_back(c);
        }
    }
    if (potentialTargets.empty()) {
        std::cout << "No target city available for rebellion attack.\n";
        return;
    }
    // Choose a random target city.
    int index = rand() % potentialTargets.size();
    City* targetCity = potentialTargets[index];

    // Use MilitaryTactics to simulate the attack.
    MilitaryTactics tactics;
    std::cout << cityName << " (rebelling) is attacking " << targetCity->cityName << "!\n";
    bool success = tactics.attackCity(playerCountry, playerCountry, *targetCity,
                                      this->army_size, targetCity->army_size,
                                      this->morale, targetCity->morale);
    if (success) {
        std::cout << "Rebels have captured " << targetCity->cityName << "!\n";
        // Decrease target city's population by the attacking (rebellious) city's population.
        int reduction = this->population;
        int oldPopulation = targetCity->population;
        targetCity->population = std::max(0, targetCity->population - reduction);
        std::cout << targetCity->cityName << " loses " << reduction 
                  << " people due to the rebellion attack (Population: " 
                  << oldPopulation << " -> " << targetCity->population << ").\n";
        targetCity->isRebelling = true;
    } else {
        std::cout << "The rebellion attack on " << targetCity->cityName << " failed.\n";
    }
}
