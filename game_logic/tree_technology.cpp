#include "technology_tree.h"
#include <algorithm>

TechNode::TechNode(const std::string &name, const std::string &description, int cost, TechType type)
    : name(name), description(description), cost(cost), type(type), unlocked(false) {}

bool TechNode::canUnlock() const {
    // Check that all prerequisite nodes are unlocked.
    for (auto prereq : prerequisites) {
        if (!prereq->unlocked)
            return false;
    }
    return true;
}

void TechNode::unlock() {
    unlocked = true;
}

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
                // Apply each stat bonus from the node.
                for (const auto &bonus : node->statBonuses) {
                    const std::string &attr = bonus.first;
                    int value = bonus.second;
                    if (attr == "population") {
                        features.population += value;
                    } else if (attr == "happiness") {
                        features.happiness += value;
                    } else if (attr == "money") {
                        features.money += value;
                    } else if (attr == "manpower") {
                        features.manpower += value;
                    } else if (attr == "metal") {
                        features.metal += value;
                    } else if (attr == "wood") {
                        features.wood += value;
                    } else if (attr == "stone") {
                        features.stone += value;
                    } else if (attr == "food") {
                        features.food += value;
                    } else if (attr == "water") {
                        features.water += value;
                    } else if (attr == "technology") {
                        features.technology += value;
                    } else if (attr == "military_experience") {
                        features.military_experience += value;
                    } else if (attr == "unrest") {
                        features.unrest += value;
                    } else if (attr == "morale") {
                        features.morale += value;
                    } else if (attr == "movement") {
                        features.movement += value;
                    } else if (attr == "mortality_rate") {
                        features.mortality_rate += value;
                    } else if (attr == "diseases_rate") {
                        features.diseases_rate += value;
                    }
                    // For land-related stats (land_fertility, water_production, etc.)
                    // you would need to update the appropriate structure (e.g., City or Land) accordingly.
                }
            } else if (node->type == TechType::LEADER) {
                // If no special leader is set, assign the leader bonus.
                if (features.leader.name == "Default Leader")
                    features.leader = node->leaderBonus;
            } else if (node->type == TechType::ALLIANCE) {
                // Merge alliance bonus by adding members.
                for (const auto &member : node->allianceBonus.members)
                    features.alliances.addMember(member);
            }
        }
    }
}
