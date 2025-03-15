#include <iostream>
#include <vector>

class Leader {
    public:
        std::string name;
        int experience;
        int leadership_skill;
        int popularity;
        
        Leader(std::string n = "Unknown", int exp = 0, int skill = 0, int pop = 0)
            : name(n), experience(exp), leadership_skill(skill), popularity(pop) {}
};

class Groups {
    public:
        std::vector<std::string> members;
        void addMember(std::string member) {
            members.push_back(member);
        }
        void startGame() {

        }
};

class Features {
    public:
        int water_supply;
        int food_supply;
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
        Leader leader;
        Groups alliances;
        
        Features() : water_supply(100), food_supply(100), population(100), happiness(50), 
                     money(500), manpower(50), metal(50), wood(50), stone(50), 
                     food(100), water(100), technology(0), military_experience(0), 
                     unrest(0), morale(50) {}
};

class Land {
    public:
        int size;
        int fertility;
        int water;
        int wood;
        int stone;
        int metal;
        int food;
        int population;
        int technology;
        Features features;
        Groups groups;
        
        Land(int sz = 100, int fert = 50, int wat = 100, int wd = 50, int st = 50, int mt = 50, int fd = 100, int pop = 100, int tech = 0) 
            : size(sz), fertility(fert), water(wat), wood(wd), stone(st), metal(mt), food(fd), population(pop), technology(tech) {}
};

class GameLogic {
    public:
        void startGame() {
            // Initialize game logic, setup conditions
        }
};

class Game {
    public:
        GameLogic logic;
        Groups groups;
        void startGame() {
            logic.startGame();
            groups.startGame();
        }
};
