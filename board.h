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

    // Vectors representing all criteria and goals
    std::vector<std::shared_ptr<Criterion>> criteria;
    std::vector<std::shared_ptr<Goal>> goals;

    // Map of criteria to their adjacent criteria and goals
    std::map<int, std::pair<std::set<int>, std::set<int>>> criterionMap;

    // Generate criteria and goals
    void generateCriteriaAndGoals();

    // Populate the criterion map with adjacency data
    void populateCriterionMap();

    // Output number in specified board format
    void outputNum(int num) const;

public:
    // Constructor
    Board(std::unique_ptr<BoardSetup> setup);

    // Check if it's valid to complete/build at a specific criterion
    bool canBuildCriteria(int criterionId, const Student& student, bool begin) const;
    // Check if it's valid to achieve/build at a specific goal
    bool canBuildGoal(int goalId, const Student& student) const;
    // Checks if adjacent criteria to a specific criterion are empty
    bool emptyAdjacent(int criterionId) const;
    // Checks if a specific goal has been achieved by player/student
    bool ownsGoal(int criterionId, const Student &student) const;
    // Returns a pointer to the tile that the geese is on
    Tile* getGeeseLocation(); 
    // Displays the board
    void display() const;
    // Returns criteria vector
    const std::vector<std::shared_ptr<Criterion>>& getCriteria() const; 
    // Returns goals vector
    const std::vector<std::shared_ptr<Goal>>& getGoals() const;
    // Returns raw pointer to the criterion with the given id
    Criterion* getCriterion(int criterionId) const; 
    // Returns raw pointer to the goal with the given id
    Goal* getGoal(int goalId) const;
    // Returns tiles vector
    const std::vector<std::unique_ptr<Tile>>& getTiles() const;
    // Returns a string of the board data
    std::string getData() const;

    bool isValid(int criterionId) const; ////// DELETE LATER
};

#endif
