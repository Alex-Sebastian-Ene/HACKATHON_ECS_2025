#include "negotation.h"
#include <iostream>
#include <algorithm>

void Negotiation::attemptAttackOrNegotiate(Country &attacker, Country &defender, City &targetCity, 
                                             int attackingForce, int defendingForce, 
                                             double attackerMorale, double defenderMorale) {
    // Calculate effective strengths based on force and morale.
    // Here, morale is assumed as a percentage (with 100 being baseline).
    double attackerEffective = attackingForce * (attackerMorale / 100.0);
    double defenderEffective = defendingForce * (defenderMorale / 100.0);
    
    // Calculate win probability from effective strengths.
    double winProbability = 0.0;
    if ((attackerEffective + defenderEffective) > 0)
        winProbability = attackerEffective / (attackerEffective + defenderEffective);
    
    std::cout << "Calculated win probability: " << winProbability << std::endl;
    
    // Define a threshold below which it is preferable to negotiate.
    const double threshold = 0.5; // 50%
    
    MilitaryTactics tactics; // Reuse our tactics module.
    
    if (winProbability < threshold) {
        std::cout << "Win probability is low (" << winProbability 
                  << "). Opting for negotiation instead of attack." << std::endl;
        // Try to negotiate a ceasefire.
        bool negotiated = tactics.negotiateCeasefire(attacker, defender);
        if (negotiated) {
            std::cout << "Negotiation successful. No attack will be carried out." << std::endl;
        } else {
            std::cout << "Negotiation failed. Proceeding with attack as a last resort." << std::endl;
            auto casualties = tactics.simulateBattle(attackingForce, defendingForce, attackerMorale, defenderMorale);
            std::cout << "Attack executed. Casualties: " << casualties.first 
                      << " attackers, " << casualties.second << " defenders." << std::endl;
        }
    } else {
        std::cout << "Win probability is favorable (" << winProbability 
                  << "). Proceeding with attack." << std::endl;
        auto casualties = tactics.simulateBattle(attackingForce, defendingForce, attackerMorale, defenderMorale);
        std::cout << "Attack executed. Casualties: " << casualties.first 
                  << " attackers, " << casualties.second << " defenders." << std::endl;
    }
}
