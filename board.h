#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <set>
#include "tile.h"
#include "boardsetup.h"
#include "student.h"
#include "resource.h"

class Board {
private:
    // Tiles on the board
    std::vector<std::unique_ptr<Tile>> tiles;

    // Hard-coded criteria and goals
    std::vector<std::shared_ptr<Criterion>> criteria;
    std::vector<std::shared_ptr<Goal>> goals;

    // Map of criteria to their adjacent criteria and goals
    std::map<int, std::pair<std::set<int>, std::set<int>>> criterionMap;


    // Generate criteria and goals
    void generateCriteriaAndGoals();

    // Populate the criterion map with adjacency data
    void populateCriterionMap();

public:
    // Constructor
    Board(std::unique_ptr<BoardSetup> setup);

    // Check if it's valid to build at a specific location
    bool canBuildCriteria(int criterionId, const Student& student) const;

    bool canBuildGoal(int goalId, const Student& student) const;

    bool isValid(int criterionId) const;

    // Get adjacent criteria for a given criterion ID
    bool emptyAdjacent(int criterionId) const;

    bool ownsGoal(int criterionId, const Student &student) const;
    Tile* getGeeseLocation(); 

    // Display the board
    void display() const;

    // Returns criteria vector
    const std::vector<std::shared_ptr<Criterion>>& getCriteria() const; 

    Criterion* getCriterion(int criterionId) const; // returns raw pointer to the criterion with the given id
    Goal* getGoal(int goalId) const;
    
    // Returns goals vector
    const std::vector<std::shared_ptr<Goal>>& getGoals() const;

    // Returns tiles vector
    const std::vector<std::unique_ptr<Tile>>& getTiles() const;

    // Returns a string of the board data
    std::string getData() const;
};

#endif