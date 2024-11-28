#include <string>
#include <iostream>
#include <fstream>
#include "board.h"
using namespace std;

Board::Board(std::unique_ptr<BoardSetup> setup) {
    generateCriteriaAndGoals();
    tiles = setup->generateTiles(criteria, goals);
    populateCriterionMap();
}


// Generate criteria and goals
void Board::generateCriteriaAndGoals() {
    // Generate 53 criteria with initial costs (assignment cost)
    for (int i = 0; i < 53; ++i) {
        criteria.push_back(std::make_shared<Criterion>(i));
    }

    // Generate 71 goals with fixed costs
    for (int i = 0; i < 71; ++i) {
        goals.push_back(std::make_shared<Goal>(i));
    }
}

void Board::populateCriterionMap() {
    // TEMP CODE
    for (int i = 0; i < 53; ++i) {
        std::set<int> adjacentCriteria;
        std::set<int> adjacentGoals;
        for (int j = -1; j <= 1; ++j) { 
            adjacentCriteria.insert(j);
        }
        for (int j = -1; j <= 1; ++j) {
         
            adjacentGoals.insert(j);
        }
        criterionMap[i] = {adjacentCriteria, adjacentGoals};
    }
}

// Check if it's valid to build at a specific location
bool Board::canBuild(int criterionId, const Student& student) const {
    // Check if criteria is already owned
    if (getCriterion(criterionId)->isOwned()) {return false;}

    const auto& [adjCriteria, adjGoals] = criterionMap.at(criterionId);

    // Check if no one owns adjacent criteria
    for (int adj : adjCriteria) {
        if (getCriterion(adj)->isOwned()) {
            return false;
        }
    }

    // Check if the student owns at least one adjacent goal
    for (int adj : adjGoals) {
        if (getGoal(adj)->getOwnerName() == student.getColour()) {
            return true;
        }
    }

    return false;
}

bool Board::isValid(int criterionId) const {
    return true;
}

// Returns true if no adjacent criteria to a given a criterionId is owned 
bool Board::emptyAdjacent(int criterionId) const {
    const auto& [adjCriteria, adjGoals] = criterionMap.at(criterionId);
    for (int adj : adjCriteria) {
        if (getCriterion(adj)->isOwned()) {
            return false;
        }
    }
    return true;
}

// Return raw pointer of tile that has geese
Tile* Board::getGeeseLocation() {
    for (const auto& tile : tiles) {
        if (tile->hasGeese()) {
            return tile.get();
        }
    }
    return nullptr;
}



void Board::display() const {
    ifstream inputFile("board.txt");

     if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return;
    }

    char ch;

    // Read character by character
    int goalIndex = 0, criteriaIndex = 0, index = 0, rollIndex = 0, tileIndex = 0;

    while (inputFile.get(ch)) {

        if (ch == 'G') {
            if (goals[goalIndex]->isOwned()) {
                cout << goals[goalIndex]->getOwnerName()[0] << "A";
            } else {
                std::cout << goals[goalIndex]->getId();

            }
            goalIndex++;

        }   
        else if (ch=='T') {
            std::string typeString = resourceToString(tiles[tileIndex]->getType());
            cout << typeString;
            for (int i = 0; i < typeString.length() - 1; i++) {inputFile.get(ch);}
            tileIndex++;
        }
        else if (ch=='C') {
            if (criteria[criteriaIndex]->isOwned()) {
                cout << criteria[criteriaIndex]->getOwnerName()[0];
                switch (criteria[criteriaIndex]->getCompletion())
                {
                case 1:
                    std::cout << "A";
                    break;
                case 2:
                    std::cout << "M";
                    break;
                case 3:
                    std::cout << "E";
                    break;
                
                default:
                    std::cout << criteria[criteriaIndex]->getId();
                    break;
                }

            } else {
                std::cout << criteria[criteriaIndex]->getId();

            }
            criteriaIndex++;
        }
        else if (ch=='I') {
            std::cout << index;
            index++;
        }
        else if (ch=='R') { 
            std::cout << tiles[rollIndex]->getValue();
            rollIndex++;
        }
        else {
            cout << ch;
        }
        
    }
}

// returns raw pointer to the criterion with the given id
Criterion* Board::getCriterion(int criterionId) const {
    for (auto criterion: criteria) {
        if (criterion->getId() == criterionId) {
            return criterion.get();
        }
    }
    return nullptr;
}

// returns raw pointer to the goal with the given id
Goal* Board::getGoal(int goalId) const {
    for (auto goal: goals) {
        if (goal->getId() == goalId) {
            return goal.get();
        }
    }
    return nullptr;
}

// Returns criteria vector
const std::vector<std::shared_ptr<Criterion>>& Board::getCriteria() const {
    return criteria;
}

// Returns goals vector
const std::vector<std::shared_ptr<Goal>>& Board::getGoals() const {
    return goals;
}


// Returns tiles vector
const std::vector<std::unique_ptr<Tile>>& Board::getTiles() const {
    return tiles;
}
