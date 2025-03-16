#include "population_growth.h"

PopulationSimulation::PopulationSimulation(int days, double P0, double K, double food_supply)
    : days(days), P(P0), K(K), food_supply(food_supply), E(0.0),
      birth_rate_daily(2.1 / 365.0), death_rate_base_daily(2.0 / 365.0),
      alpha(1.0), beta(1.0), gamma(3.0),
      m0(-0.001), lambda_migration(0.0005), econ_sensitivity(10.0),
      p_war(0.01), war_duration(3), war_timer(0),
      p_random(0.005), random_impact(0.05) {
    rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
}

void PopulationSimulation::run() {
    for (int day = 1; day <= days; ++day) {
        if (war_timer == 0 && randomDouble() < p_war) {
            war_timer = war_duration;
        }

        double W = (war_timer > 0) ? 1.0 : 0.0;
        if (war_timer > 0) {
            war_timer--;
        }

        double R = (P > food_supply) ? (P - food_supply) / food_supply : 0.0;
        double effective_death_rate = death_rate_base_daily * (1 + alpha * (P / K) + beta * R + gamma * W);
        double netMigrationRate = m0 + lambda_migration * E;

        double delta_P_random = 0.0;
        if (randomDouble() < p_random) {
            delta_P_random = -random_impact * P;
            E -= 5;
        }

        double dP_dt = P * (birth_rate_daily - effective_death_rate + netMigrationRate) + delta_P_random;
        P += dP_dt;
        if (P < 0) P = 0;

        E += econ_sensitivity * netMigrationRate;
        double militaryPower = 0.4 * P;

        PopulationData data = {day, P, militaryPower, E, W, netMigrationRate};
        history.push_back(data);
    }
}

void PopulationSimulation::printSummary(int numDays) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Day\tPopulation\tMil.Power\tEconomy\tWarIntensity\tNetMigration\n";
    for (size_t i = 0; i < history.size() && i < static_cast<size_t>(numDays); ++i) {
        const auto& d = history[i];
        std::cout << d.day << "\t" << d.population << "\t\t"
                  << d.militaryPower << "\t\t" 
                  << d.economy << "\t" 
                  << d.warIntensity << "\t\t" 
                  << d.netMigrationRate << "\n";
    }
}

void PopulationSimulation::updateEconomy(double newEconomy) {
    E = newEconomy;
}

double PopulationSimulation::getCurrentPopulation() const {
    return P;
}

double PopulationSimulation::randomDouble() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}
