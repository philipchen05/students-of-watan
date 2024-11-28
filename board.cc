#include <string>
#include <iostream>
#include <fstream>
#include "board.h"
#include "resource.h"
using namespace std;

Board::Board(std::unique_ptr<BoardSetup> setup) {
    generateCriteriaAndGoals();
    tiles = setup->generateTiles(criteria, goals);
    populateCriterionMap();
}


// Generate criteria and goals
void Board::generateCriteriaAndGoals() {
    // Generate 53 criteria with initial costs (assignment cost)
    for (int i = 0; i < 54; ++i) {
        criteria.push_back(std::make_shared<Criterion>(i));
    }

    // Generate 71 goals with fixed costs
    for (int i = 0; i < 72; ++i) {
        goals.push_back(std::make_shared<Goal>(i));
    }
}

void Board::populateCriterionMap() {
    criterionMap = {
        {0, {{1, 3}, {0, 1}}},
        {1, {{0, 4}, {0, 2}}},
        {2, {{3, 7}, {3, 5}}},
        {3, {{0, 2, 8}, {1, 3, 6}}},
        {4, {{1, 5, 9}, {2, 4, 7}}},
        {5, {{4, 10}, {4, 8}}},
        {6, {{7, 12}, {9, 12}}},
        {7, {{2, 6, 13}, {5, 9, 13}}},
        {8, {{3, 9, 14}, {6, 10, 14}}},
        {9, {{4, 8, 15}, {7, 10, 15}}},
        {10, {{5, 11, 16}, {8, 11, 16}}}, 
        {11, {{10, 17}, {11 , 17}}},
        {12, {{6, 18}, {12, 20}}},
        {13, {{7, 14, 19}, {13, 18, 21}}},
        {14, {{8, 13, 20}, {14, 18, 20}}},
        {15, {{9, 16, 21}, {15, 19, 23}}},
        {16, {{10, 15, 22}, {16, 19, 24}}},
        {17, {{11, 23}, {17, 25}}},
        {18, {{12, 19, 24}, {20, 26, 29}}},
        {19, {{13, 18, 25}, {21, 26, 30}}}, 
        {20, {{14, 21, 26}, {22, 27, 31}}},
        {21, {{15, 20, 27}, {23, 27, 32}}},
        {22, {{16, 23, 28}, {24, 28, 33}}},
        {23, {{17, 22, 29}, {25, 28, 34}}}, 
        {24, {{18, 30}, {29, 37}}},
        {25, {{19, 26, 31}, {30, 35, 38}}},
        {26, {{20, 25, 32}, {31, 35, 39}}},
        {27, {{21, 28, 33}, {32, 36, 40}}}, 
        {28, {{22, 27, 34}, {33, 36, 41}}},
        {29, {{23, 35}, {34, 42}}},
        {30, {{24, 31, 36}, {37, 46, 43}}},
        {31, {{25, 30, 37}, {38, 43, 47}}},
        {32, {{36, 33, 38}, {39, 44, 49}}},
        {33, {{27, 32, 39}, {40, 44, 49}}},
        {34, {{28, 35, 40}, {41, 45, 50}}}, // correct so far
        {35, {{17, 71}, {34, 70}}},
        {36, {{18, 72}, {35, 71}}},
        {37, {{19, 73}, {36, 72}}},
        {38, {{20, 74}, {37, 73}}},
        {39, {{21, 75}, {38, 74}}},
        {40, {{22, 76}, {39, 75}}},
        {41, {{23, 77}, {40, 76}}},
        {42, {{24, 78}, {41, 77}}},
        {43, {{25, 79}, {42, 78}}},
        {44, {{26, 80}, {43, 79}}},
        {45, {{27, 81}, {44, 80}}},
        {46, {{28, 82}, {45, 81}}},
        {47, {{29, 83}, {46, 82}}},
        {48, {{30, 84}, {47, 83}}},
        {49, {{31, 85}, {48, 84}}},
        {50, {{32, 86}, {49, 85}}},
        {51, {{33, 87}, {50, 86}}},
        {52, {{34, 88}, {51, 87}}},
        {53, {{35, 89}, {52, 88}}},
        {54, {{36, 90}, {53, 89}}},
        {55, {{37, 91}, {54, 90}}},
        {56, {{38, 92}, {55, 91}}},
        {57, {{39, 93}, {56, 92}}},
        {58, {{40, 94}, {57, 93}}},
        {59, {{41, 95}, {58, 94}}},
        {60, {{42, 96}, {59, 95}}},
        {61, {{43, 97}, {60, 96}}},
        {62, {{44, 98}, {61, 97}}},
        {63, {{45, 99}, {62, 98}}},
        {64, {{46, 100}, {63, 99}}},
        {65, {{47, 101}, {64, 100}}},
        {66, {{48, 102}, {65, 101}}},
        {67, {{49, 103}, {66, 102}}},
        {68, {{50, 104}, {67, 103}}},
        {69, {{51, 105}, {68, 104}}},
        {70, {{52, 106}, {69, 105}}},
        {71, {{53, 107}, {70, 106}}}
        };
}

bool Board::canBuildGoal(int goalId, const Student& student) const {
    if (getGoal(goalId)->isOwned()) {return false;}
    
    // Find adjacent criteria to goal
    for (const auto& [key, pairSet] : criterionMap) {
        const auto& adjacentGoals = pairSet.second; // Access the second set in the pair
        if (adjacentGoals.find(goalId) != adjacentGoals.end()) { // Check if goalId is in the set
            if (getCriterion(key)->getOwnerName() == student.getColour()) {return true;}
            for (int v : adjacentGoals) {
                if (getGoal(v)->getOwnerName() == student.getColour()) {return true;}
            }
        }
    }

    return false;

}
// Check if it's valid to build at a specific location
bool Board::canBuildCriteria(int criterionId, const Student& student) const {
    // Check if criteria is already owned
    if (getCriterion(criterionId)->isOwned()) {return false;}
    // cout << "Can build: isOwned " << getCriterion(criterionId)->isOwned() << endl;

    if (!emptyAdjacent(criterionId)) {return false;}

    // Check if the student owns at least one adjacent goal
    if (!ownsGoal(criterionId, student)) {return false;}

    return true;
}

bool Board::isValid(int criterionId) const {
    return true;
}

bool Board::ownsGoal(int criterionId, const Student& student) const {
    const auto& [adjCriteria, adjGoals] = criterionMap.at(criterionId);
    // Check if the student owns at least one adjacent goal
    for (int adj : adjGoals) {
        if (getGoal(adj)->getOwnerName() == student.getColour()) {
            return true;
        }
    }
    return false;

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
                inputFile.get(ch);
            } else {
                std::cout << goals[goalIndex]->getId();
                if (goals[goalIndex]->getId() >= 10) {inputFile.get(ch);}

            }
            // cout << "goal index: " << goalIndex << endl;
            goalIndex++;

        }   
        else if (ch=='T') {
            std::string typeString = resourceToString(tiles[tileIndex]->getType());
            cout << typeString;
            for (std::size_t i = 0; i < typeString.length() - 1; i++) {inputFile.get(ch);}
            tileIndex++;
        }
        else if (ch=='C') {
        // cout << "display: isOwned " << criteria[criteriaIndex]->isOwned() << endl; 
        std::cerr << *criteria[criteriaIndex] << std::endl;
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
                inputFile.get(ch);
            } else {
                std::cout << criteria[criteriaIndex]->getId();
                if (criteria[criteriaIndex]->getId() >= 10) {inputFile.get(ch);}

            }
            // cout << "criteria index: " << criteriaIndex << endl;
            criteriaIndex++;
        }
        else if (ch=='I') {
            std::cout << index;
            if (index >= 10) {inputFile.get(ch);}
            index++;
        }
        else if (ch=='R') { 
            if (tiles[rollIndex]->getValue() == 0) {std::cout << " ";}
            else {
                std::cout << tiles[rollIndex]->getValue();
                if (tiles[rollIndex]->getValue() >= 10) {inputFile.get(ch);}
            }
            rollIndex++;
        }
        else {
            cout << ch;
        }
        
    }
    inputFile.close();

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


std::string Board::getData() const {
    std::string boardData = "";
    for (const auto& tile : tiles) {
        boardData += std::to_string(resourceToInt(tile->getType()));
        boardData += " ";
        boardData += std::to_string(tile->getValue());
        if (tile->getLocation() != 18) {boardData += " ";}
        
    }
    return boardData;
}