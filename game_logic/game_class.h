#ifndef TANGGAME_H
#define TANGGAME_H

#include <iostream>
#include <vector>
#include <string>

// ----------------------
// Groups Class: For alliances and affiliations
// ----------------------
class Groups {
public:
    std::vector<std::string> members;
    void addMember(const std::string& member) {
        members.push_back(member);
    }
    void startGame() {
        std::cout << "Alliance groups are starting their operations...\n";
    }
};

// ----------------------
// Leader Base & Derived Classes
// ----------------------

// Base Leader Class
class Leader {
public:
    std::string name;
    int experience;
    int leadership_skill;
    int popularity;
    
    Leader(std::string n = "Unknown", int exp = 0, int skill = 0, int pop = 0)
        : name(n), experience(exp), leadership_skill(skill), popularity(pop) {}
    
    virtual void showDetails() {
        std::cout << "Leader: " << name << ", Exp: " << experience 
                  << ", Leadership: " << leadership_skill 
                  << ", Popularity: " << popularity << "\n";
    }
    virtual ~Leader() {}
};

// Military Leader
class MilitaryLeader : public Leader {
public:
    int combat_skill;
    int strategy_skill;
    
    MilitaryLeader(std::string n = "Unknown", int exp = 0, int skill = 0, int pop = 0, int combat = 0, int strategy = 0)
        : Leader(n, exp, skill, pop), combat_skill(combat), strategy_skill(strategy) {}

    void showDetails() override {
        std::cout << "[Military] " << name << " - Combat: " << combat_skill 
                  << ", Strategy: " << strategy_skill << "\n";
    }
};

// Industrial Leader
class IndustrialLeader : public Leader {
public:
    int productivity;
    int resource_management;
    
    IndustrialLeader(std::string n = "Unknown", int exp = 0, int skill = 0, int pop = 0, int prod = 0, int res_mgmt = 0)
        : Leader(n, exp, skill, pop), productivity(prod), resource_management(res_mgmt) {}

    void showDetails() override {
        std::cout << "[Industry] " << name << " - Productivity: " << productivity 
                  << ", Resource Management: " << resource_management << "\n";
    }
};

// Research Leader
class ResearchLeader : public Leader {
public:
    int innovation;
    int education;
    
    ResearchLeader(std::string n = "Unknown", int exp = 0, int skill = 0, int pop = 0, int innov = 0, int edu = 0)
        : Leader(n, exp, skill, pop), innovation(innov), education(edu) {}

    void showDetails() override {
        std::cout << "[Research] " << name << " - Innovation: " << innovation 
                  << ", Education: " << education << "\n";
    }
};

// Economic Leader
class EconomicLeader : public Leader {
public:
    int trade;
    int wealth_management;
    
    EconomicLeader(std::string n = "Unknown", int exp = 0, int skill = 0, int pop = 0, int trd = 0, int wealth = 0)
        : Leader(n, exp, skill, pop), trade(trd), wealth_management(wealth) {}

    void showDetails() override {
        std::cout << "[Economy] " << name << " - Trade: " << trade 
                  << ", Wealth Mgmt: " << wealth_management << "\n";
    }
};

// Political Leader
class PoliticalLeader : public Leader {
public:
    int diplomacy;
    int administration;
    
    PoliticalLeader(std::string n = "Unknown", int exp = 0, int skill = 0, int pop = 0, int diplo = 0, int admin = 0)
        : Leader(n, exp, skill, pop), diplomacy(diplo), administration(admin) {}

    void showDetails() override {
        std::cout << "[Politics] " << name << " - Diplomacy: " << diplomacy 
                  << ", Administration: " << administration << "\n";
    }
};


// ----------------------
// Features & Land Classes
// ----------------------
class Features {
    public:
        int population;
        int happiness;
        int money;
        int manpower;
        int metal;
        int wood;
        int stone;
        int food;
        int water;
        int technology;
        int military_experience;
        int unrest;
        int morale;
        int movement;
        int mortality_rate;
        int diseases_rate;
        Leader leader;
        Groups alliances;
        
        Features() : population(100),
                     happiness(50), money(500), manpower(50),
                     metal(50), wood(50), stone(50),
                     food(100), water(100), technology(0),
                     military_experience(0), unrest(0), morale(50),
                     movement(0), mortality_rate(0), diseases_rate(0),
                     leader("Default Leader", 0, 0, 0) {}
    };
    
class Land {
public:
    int size;
    int land_fertility;
    int water_production;
    int wood_production;
    int stone_production;
    int metal_production;
    int food_production;
    int flooding_rate;
    bool drought;
    
    Land(int sz = 100, int fert = 50, int water = 100, int wood = 50, int stone = 50, int metal = 50, int food = 100)
        : size(sz), land_fertility(fert), water_production(water), wood_production(wood), 
            stone_production(stone), metal_production(metal), food_production(food), 
            flooding_rate(10), drought(false) {}
};

// ----------------------
// City Class
// ----------------------
// A City inherits from Features and Land so it carries both internal
// properties and geographical data. It can also be extended with event handling.
class City : public Features, public Land {
    public:
        std::string cityName;   // Name of the city
        
        // Constructor initializes the Land portion and sets the city name.
        City(const std::string& name, int landSize = 100, int fert = 50, int water = 100, int wood = 50, 
             int stone = 50, int metal = 50, int food = 100)
            : Land(landSize, fert, water, wood, stone, metal, food), cityName(name) {}
        
        void showDetails() {
            std::cout << "City: " << cityName << "\n";
            std::cout << "Population: " << population << "\n";
            std::cout << "Water Supply: " << water << "\n";
            std::cout << "Food Supply: " << food << "\n";
            std::cout << "Land Size: " << size << "\n";
            std::cout << "Land Fertility: " << land_fertility << "\n";
            std::cout << "Leader: " << leader.name << "\n";
        }
    };
    
// A Country aggregates multiple cities and has its own leader.
class Country {
    public:
        std::string countryName;         // Name of the country
        std::vector<City*> cities;         // List of cities in the country
        Leader leader;                   // Country's leader
        
        Country(const std::string& name, const Leader& ldr = Leader("Country Leader", 10, 10, 10))
            : countryName(name), leader(ldr) {}
        
        void addCity(City* city) {
            cities.push_back(city);
        }
        
        void showDetails() {
            std::cout << "Country: " << countryName << "\n";
            std::cout << "Leader: " << leader.name << "\n";
            std::cout << "Number of Cities: " << cities.size() << "\n";
            for (auto city : cities) {
                std::cout << "-----------------------\n";
                city->showDetails();
            }
        }
    };
 
// ----------------------
// Group Class: Combining Everything
// ----------------------

// Group class represents a faction with its own resources, territory, and leaders.
class Group {
    public:
        std::string group_name;
        Land land;
        Features features;
        std::vector<Leader*> leaders;
        int money;
        int military_power;
        int stability;
    
        Group(std::string name, int landSize = 100, int fert = 50)
            : group_name(name), land(landSize, fert), money(500), military_power(100), stability(80) {}
    
        void addLeader(Leader* leader) {
            leaders.push_back(leader);
        }
    
        void showGroupDetails() {
            std::cout << "=== Group: " << group_name << " ===\n";
            std::cout << "  Population: " << features.population << "\n";
            std::cout << "  Money: " << money << "\n";
            std::cout << "  Military Power: " << military_power << "\n";
            std::cout << "  Stability: " << stability << "\n";
            std::cout << "  Leaders:\n";
            for (auto leader : leaders) {
                leader->showDetails();
            }
            std::cout << "===========================\n";
        }
    
        void checkEconomy() {
            if (money <= 0) {
                std::cout << "⚠️ Economic crisis in " << group_name << "! Trade policies must change!\n";
            }
        }
    
        void warDeclared() {
            std::cout << "⚔️ War started involving " << group_name << "!\n";
            military_power -= 10;
        }
    };
    


// ----------------------
// Game Logic & Game Classes
// ----------------------

class GameLogic {
public:
    void startGame() {
        std::cout << "The Tang Dynasty simulation begins! Consolidate your power and manage your resources...\n";
    }
};

class Game {
public:
    GameLogic logic;
    Groups groups; // Represents overarching alliances or factions
    std::vector<Group> factions; // Main groups (factions) in the game

    void addFaction(const Group& faction) {
        factions.push_back(faction);
    }

    void startGame() {
        logic.startGame();
        groups.startGame();
        for (auto& faction : factions) {
            faction.showGroupDetails();
        }
    }
};

#endif // TANGGAME_H
