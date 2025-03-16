#include "technology_tree.h"
#include <algorithm>

// -------------------
// TechNode Implementation
// -------------------
TechNode::TechNode(const std::string &name, const std::string &description, int cost, TechType type)
    : name(name), description(description), cost(cost), type(type), unlocked(false) {}

bool TechNode::canUnlock() const {
    for (auto prereq : prerequisites) {
        if (!prereq->unlocked)
            return false;
    }
    return true;
}

void TechNode::unlock() {
    unlocked = true;
}

// -------------------
// TechnologyTree Implementation
// -------------------
TechnologyTree::TechnologyTree(int initialPoints)
    : technologyPoints(initialPoints) {}

TechnologyTree::~TechnologyTree() {
    for (auto node : nodes)
        delete node;
}

void TechnologyTree::addNode(TechNode* node) {
    nodes.push_back(node);
}

bool TechnologyTree::unlockNode(const std::string &nodeName) {
    for (auto node : nodes) {
        if (node->name == nodeName && !node->unlocked) {
            if (!node->canUnlock())
                return false; // prerequisites not met
            if (technologyPoints < node->cost)
                return false; // not enough technology points

            technologyPoints -= node->cost;
            node->unlock();
            return true;
        }
    }
    return false; // node not found or already unlocked
}

void TechnologyTree::applyBonuses(Features &features) {
    for (auto node : nodes) {
        if (node->unlocked) {
            if (node->type == TechType::STAT_BOOST) {
                for (const auto &bonus : node->statBonuses) {
                    const std::string &attr = bonus.first;
                    int value = bonus.second;
                    if      (attr == "population")          features.population += value;
                    else if (attr == "happiness")           features.happiness += value;
                    else if (attr == "money")               features.money += value;
                    else if (attr == "manpower")            features.manpower += value;
                    else if (attr == "metal")               features.metal += value;
                    else if (attr == "wood")                features.wood += value;
                    else if (attr == "stone")               features.stone += value;
                    else if (attr == "food")                features.food += value;
                    else if (attr == "water")               features.water += value;
                    else if (attr == "technology")          features.technology += value;
                    else if (attr == "military_experience") features.military_experience += value;
                    else if (attr == "unrest")              features.unrest += value;
                    else if (attr == "morale")              features.morale += value;
                    else if (attr == "movement")            features.movement += value;
                    else if (attr == "mortality_rate")      features.mortality_rate += value;
                    else if (attr == "diseases_rate")       features.diseases_rate += value;
                }
            } else if (node->type == TechType::LEADER) {
                if (features.leader.name == "Default Leader")
                    features.leader = node->leaderBonus;
            } else if (node->type == TechType::ALLIANCE) {
                for (auto &member : node->allianceBonus.members)
                    features.alliances.addMember(member);
            }
        }
    }
}

// -------------------
// createTechnologyTree Implementation
// -------------------
TechnologyTree* createTechnologyTree(int initialPoints) {
    TechnologyTree* tree = new TechnologyTree(initialPoints);

    // 1) Root node: "Establish Technical cities"
    TechNode* establishTechnicalCities = new TechNode(
        "Establish Technical cities",
        "Lay the foundation for advanced knowledge and specialized training.",
        50,
        TechType::STAT_BOOST
    );
    tree->addNode(establishTechnicalCities);

    // 2) "military experience +100 technology +50"
    TechNode* milTech = new TechNode(
        "military experience +100 technology +50",
        "Boost your forces and research capabilities.",
        100,
        TechType::STAT_BOOST
    );
    milTech->prerequisites.push_back(establishTechnicalCities);
    milTech->statBonuses["military_experience"] = 100;
    milTech->statBonuses["technology"]         = 50;
    tree->addNode(milTech);

    // 3) "morale +50 war on the stuff countries"
    TechNode* moraleWar = new TechNode(
        "morale +50 war on the stuff countries",
        "Improve morale in preparation for conflict.",
        120,
        TechType::STAT_BOOST
    );
    moraleWar->prerequisites.push_back(milTech);
    moraleWar->statBonuses["morale"] = 50;
    tree->addNode(moraleWar);

    // 4) "towards guilds to develop workers"
    TechNode* guildsWorkers = new TechNode(
        "towards guilds to develop workers",
        "Enhance your workforce and craft skills.",
        130,
        TechType::STAT_BOOST
    );
    guildsWorkers->prerequisites.push_back(moraleWar);
    guildsWorkers->statBonuses["manpower"] = 100;
    tree->addNode(guildsWorkers);

    // 5) "military +100 manpower +100"
    TechNode* militaryManpower = new TechNode(
        "military +100 manpower +100",
        "Grow your army’s size and capacity.",
        140,
        TechType::STAT_BOOST
    );
    militaryManpower->prerequisites.push_back(moraleWar);
    militaryManpower->statBonuses["military_experience"] = 100;
    militaryManpower->statBonuses["manpower"]            = 100;
    tree->addNode(militaryManpower);

    // 6) "Built a new school"
    TechNode* builtNewSchool = new TechNode(
        "Built a new school",
        "Expand education to produce advanced knowledge.",
        60,
        TechType::STAT_BOOST
    );
    builtNewSchool->prerequisites.push_back(establishTechnicalCities);
    builtNewSchool->statBonuses["technology"] = 25;
    tree->addNode(builtNewSchool);

    // 7) "stance +50 new library"
    TechNode* stanceLibrary = new TechNode(
        "stance +50 new library",
        "Boost public knowledge and cultural stance.",
        70,
        TechType::STAT_BOOST
    );
    stanceLibrary->prerequisites.push_back(builtNewSchool);
    stanceLibrary->statBonuses["happiness"] = 50;
    tree->addNode(stanceLibrary);

    // 8) "built ground built ???"
    TechNode* builtGround = new TechNode(
        "built ground built ???",
        "Expand infrastructure for future developments.",
        80,
        TechType::STAT_BOOST
    );
    builtGround->prerequisites.push_back(stanceLibrary);
    builtGround->statBonuses["wood"] = 100;
    tree->addNode(builtGround);

    // 9) "diseases rate -10 mortality rate -10"
    TechNode* diseaseMortality = new TechNode(
        "diseases rate -10 mortality rate -10",
        "Improve healthcare and reduce fatality rates.",
        90,
        TechType::STAT_BOOST
    );
    diseaseMortality->prerequisites.push_back(builtGround);
    diseaseMortality->statBonuses["diseases_rate"]  = -10;
    diseaseMortality->statBonuses["mortality_rate"] = -10;
    tree->addNode(diseaseMortality);

    // 10) "establish new city frontier"
    TechNode* newCityFrontier = new TechNode(
        "establish new city frontier",
        "Expand your territory by founding a new city.",
        80,
        TechType::STAT_BOOST
    );
    newCityFrontier->prerequisites.push_back(establishTechnicalCities);
    newCityFrontier->statBonuses["population"] = 100;
    tree->addNode(newCityFrontier);

    // 11) "happiness +200 new king popular"
    TechNode* newKingPopular = new TechNode(
        "happiness +200 new king popular",
        "A beloved leader improves morale across the realm.",
        200,
        TechType::STAT_BOOST
    );
    newKingPopular->prerequisites.push_back(newCityFrontier);
    newKingPopular->statBonuses["happiness"] = 200;
    tree->addNode(newKingPopular);

    // 12) "water +1000 for all cities"
    TechNode* water1000 = new TechNode(
        "water +1000 for all cities",
        "Securing massive water resources.",
        150,
        TechType::STAT_BOOST
    );
    water1000->prerequisites.push_back(newCityFrontier);
    water1000->statBonuses["water"] = 1000;
    tree->addNode(water1000);

    // 13) "wood +1000 for all cities"
    TechNode* wood1000 = new TechNode(
        "wood +1000 for all cities",
        "Establish sustainable lumber production.",
        150,
        TechType::STAT_BOOST
    );
    wood1000->prerequisites.push_back(newCityFrontier);
    wood1000->statBonuses["wood"] = 1000;
    tree->addNode(wood1000);

    // 14) "new metal mine"
    TechNode* newMetalMine = new TechNode(
        "new metal mine",
        "Open a new mining operation to extract metals.",
        150,
        TechType::STAT_BOOST
    );
    newMetalMine->prerequisites.push_back(newCityFrontier);
    newMetalMine->statBonuses["metal"] = 1000;
    tree->addNode(newMetalMine);

    // 15) "Employ more workforce from different ???"
    TechNode* moreWorkforce = new TechNode(
        "Employ more workforce from different ???",
        "Diverse labor force accelerates development.",
        150,
        TechType::STAT_BOOST
    );
    moreWorkforce->prerequisites.push_back(newMetalMine);
    moreWorkforce->statBonuses["manpower"] = 200;
    tree->addNode(moreWorkforce);

    // 16) "Colect crops from central ???"
    TechNode* collectCrops = new TechNode(
        "Colect crops from central ???",
        "Improve agricultural output by reorganizing farmland.",
        150,
        TechType::STAT_BOOST
    );
    collectCrops->prerequisites.push_back(moreWorkforce);
    collectCrops->statBonuses["food"] = 500;
    tree->addNode(collectCrops);

    return tree;
}
