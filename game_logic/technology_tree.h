#ifndef TECHNOLOGY_TREE_H
#define TECHNOLOGY_TREE_H

#include <string>
#include <vector>
#include <unordered_map>
#include "game_class.h" // For Leader, Groups, and Features

enum class TechType {
    STAT_BOOST,
    LEADER,
    ALLIANCE
};

class TechNode {
public:
    std::string name;
    std::string description;
    int cost; // Technology points required
    TechType type;
    bool unlocked;
    std::vector<TechNode*> prerequisites;

    // For STAT_BOOST, bonus values stored as attribute name -> bonus value.
    std::unordered_map<std::string, int> statBonuses;

    // For LEADER and ALLIANCE types.
    Leader leaderBonus;
    Groups allianceBonus;

    TechNode(const std::string &name, const std::string &description, int cost, TechType type);

    // Checks if all prerequisites have been unlocked.
    bool canUnlock() const;

    // Unlocks this node.
    void unlock();
};

class TechnologyTree {
public:
    int technologyPoints; // Available technology points.
    std::vector<TechNode*> nodes;

    TechnologyTree(int initialPoints);
    ~TechnologyTree();

    // Add a tech node to the tree.
    void addNode(TechNode* node);

    // Attempts to unlock a node by name; returns true if successful.
    bool unlockNode(const std::string &nodeName);

    // Apply bonuses from all unlocked nodes to the given Features.
    void applyBonuses(Features &features);
};

#endif // TECHNOLOGY_TREE_H
