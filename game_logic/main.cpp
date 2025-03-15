#include "game_class.h"

int main() {
    Game tangDynastyGame;
    
    // Create a faction representing the Tang Empire
    Group tangEmpire("Tang Empire", 50000, 70);
    
    // Create specialized leaders
    MilitaryLeader* general = new MilitaryLeader("Li Jing", 15, 85, 70, 90, 80);
    IndustrialLeader* engineer = new IndustrialLeader("Yuwen Kai", 10, 70, 60, 80, 75);
    ResearchLeader* scholar = new ResearchLeader("Xuanzang", 20, 90, 85, 95, 90);
    EconomicLeader* merchant = new EconomicLeader("Lu Zhaolin", 12, 75, 65, 85, 80);
    PoliticalLeader* chancellor = new PoliticalLeader("Wei Zheng", 18, 80, 75, 88, 92);
    
    // Add leaders to the Tang Empire faction
    tangEmpire.addLeader(general);
    tangEmpire.addLeader(engineer);
    tangEmpire.addLeader(scholar);
    tangEmpire.addLeader(merchant);
    tangEmpire.addLeader(chancellor);

    tangEmpire.features.alliances.addMember("Northern Alliance");
    tangEmpire.land.groups.addMember("Silk Road Consortium");
    
    // Add faction to the game
    tangDynastyGame.addFaction(tangEmpire);
    
    // Start the game simulation
    tangDynastyGame.startGame();
    

    delete general;
    delete engineer;
    delete scholar;
    delete merchant;
    delete chancellor;
    
    return 0;
}
