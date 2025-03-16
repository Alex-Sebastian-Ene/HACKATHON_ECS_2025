#ifndef MILITARY_TACTICS_H
#define MILITARY_TACTICS_H

#include <random>
#include <utility>
#include "game_class.h"  // For Country, City, Leader, Groups, etc.

class MilitaryTactics {
public:
    MilitaryTactics();

    // Simulate an attack on a city.
    // Returns true if the attack is successful (city captured), false otherwise.
    // Optional morale parameters affect effective combat strength.
    bool attackCity(Country &attacker, Country &defender, City &targetCity,
                    int attackingForce, int defendingForce,
                    double attackerMorale = 100.0, double defenderMorale = 100.0);

    // Sends a garrison to a city (for defense).
    void sendGarrison(City &city, int garrisonSize);

    // Simulate a battle between two forces.
    // Returns a pair of casualties: <attacker casualties, defender casualties>.
    // Morale parameters (default 100) adjust the effective fighting strength.
    std::pair<int, int> simulateBattle(int attackingForce, int defendingForce,
                                       double attackerMorale = 100.0, double defenderMorale = 100.0);

    // Diplomatic function: negotiate a ceasefire between two countries.
    bool negotiateCeasefire(Country &country1, Country &country2);

    // Request reinforcements for a city.
    void requestReinforcements(City &city, int reinforcementForce);

private:
    std::mt19937 rng;
    double randomDouble(double min, double max);
};

#endif // MILITARY_TACTICS_H
