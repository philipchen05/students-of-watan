#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <set>
#include "tile.h"
#include "boardsetup.h"

class Board {
private:
    // Tiles on the board
    std::vector<std::unique_ptr<Tile>> tiles;

    // Hard-coded criteria and goals
    std::vector<std::unique_ptr<Criterion>> criteria;
    std::vector<std::unique_ptr<Goal>> goals;

    // Map of criteria to their adjacent criteria and goals
    std::map<int, std::pair<std::set<int>, std::set<int>>> criterionMap;

    // Generate criteria and goals
    void generateCriteriaAndGoals();
    
    // Generate tiles and assign corresponding criteria and goals
    void generateTiles();

    // Populate the criterion map with adjacency data
    void populateCriterionMap();

public:
    // Constructor
    Board(std::unique_ptr<BoardSetup> setup);

    // Check if it's valid to build at a specific location
    bool canBuild(int criterionId, const Student& student) const;

    // Get adjacent criteria and goals for a given criterion ID
    std::pair<std::set<int>, std::set<int>> getAdjacent(int criterionId) const;

    // Display the board
    void display() const;
};

#endif