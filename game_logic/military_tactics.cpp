#include "military_tactics.h"
#include <iostream>

MilitaryTactics::MilitaryTactics() {
    std::random_device rd;
    rng.seed(rd());
}

double MilitaryTactics::randomDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
}

std::pair<int, int> MilitaryTactics::simulateBattle(int attackingForce, int defendingForce,
                                                      double attackerMorale, double defenderMorale) {
    // Generate random multipliers to simulate changing battlefield conditions.
    double attackerMultiplier = randomDouble(0.8, 1.2);
    double defenderMultiplier = randomDouble(0.8, 1.2);

    // Calculate effective strength factoring in morale (assumed as a percentage, with 100 as baseline).
    double attackerEffective = attackingForce * attackerMultiplier * (attackerMorale / 100.0);
    double defenderEffective = defendingForce * defenderMultiplier * (defenderMorale / 100.0);

    int attackerCasualties, defenderCasualties;
    if (attackerEffective > defenderEffective) {
        // Attacker wins: lower casualty percentage for attackers.
        attackerCasualties = static_cast<int>(attackingForce * randomDouble(0.1, 0.2));
        defenderCasualties = static_cast<int>(defendingForce * randomDouble(0.3, 0.5));
    } else {
        // Defender wins: higher casualties for attackers.
        attackerCasualties = static_cast<int>(attackingForce * randomDouble(0.3, 0.5));
        defenderCasualties = static_cast<int>(defendingForce * randomDouble(0.1, 0.2));
    }
    return {attackerCasualties, defenderCasualties};
}

bool MilitaryTactics::attackCity(Country &attacker, Country &defender, City &targetCity,
                                 int attackingForce, int defendingForce,
                                 double attackerMorale, double defenderMorale) {
    std::cout << attacker.countryName << " is attacking " << targetCity.cityName
              << " of " << defender.countryName << std::endl;

    auto casualties = simulateBattle(attackingForce, defendingForce, attackerMorale, defenderMorale);
    std::cout << "Battle result: Attacker casualties = " << casualties.first
              << ", Defender casualties = " << casualties.second << std::endl;

    int remainingAttackers = attackingForce - casualties.first;
    int remainingDefenders = defendingForce - casualties.second;

    if (remainingAttackers > remainingDefenders) {
        std::cout << "Attack successful! " << targetCity.cityName << " has been captured." << std::endl;
        
        return true;
    } else {
        std::cout << "Attack failed! " << targetCity.cityName << " remains under enemy control." << std::endl;
        return false;
    }
}

void MilitaryTactics::sendGarrison(City &city, int garrisonSize) {
    std::cout << "A garrison of size " << garrisonSize
              << " has been sent to " << city.cityName << "." << std::endl;
    city.army_size += garrisonSize;
}

bool MilitaryTactics::negotiateCeasefire(Country &country1, Country &country2) {
    // A simple diplomatic negotiation simulation.
    std::cout << "Negotiating ceasefire between " << country1.countryName
              << " and " << country2.countryName << "..." << std::endl;
    double chance = randomDouble(0.0, 1.0);
    if (chance > 0.5) {
        std::cout << "Ceasefire agreement reached!" << std::endl;
        return true;
    } else {
        std::cout << "Negotiations failed. No ceasefire agreement." << std::endl;
        return false;
    }
}

void MilitaryTactics::requestReinforcements(City &city, int reinforcementForce) {
    std::cout << "Reinforcements of " << reinforcementForce
              << " units have been sent to " << city.cityName << "." << std::endl;
    city.army_size += reinforcementForce;
}
