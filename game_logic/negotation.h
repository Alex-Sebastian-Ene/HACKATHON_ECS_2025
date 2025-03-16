#ifndef NEGOTIATION_H
#define NEGOTIATION_H

#include "game_world.h"       // For Country and City definitions
#include "military_tactics.h" // For using existing tactics functions

class Negotiation {
public:
    // Decides whether to attack or negotiate based on calculated win probability.
    static void attemptAttackOrNegotiate(Country &attacker, Country &defender, City &targetCity, 
                                           int attackingForce, int defendingForce, 
                                           double attackerMorale, double defenderMorale);
};

#endif // NEGOTIATION_H
