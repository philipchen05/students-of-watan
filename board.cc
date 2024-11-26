#include <string>
#include <iostream>
#include <fstream>
#include "board.h"
using namespace std;

Board::Board(std::unique_ptr<BoardSetup> setup) {
    generateCriteriaAndGoals();
    tiles = setup->generateTiles();
    populateCriterionMap();
}


// Generate criteria and goals
void Board::generateCriteriaAndGoals() {
    // Generate 53 criteria with initial costs (assignment cost)
    for (int i = 0; i < 53; ++i) {
        criteria.push_back(std::make_unique<Criterion>(i));
    }

    // Generate 71 goals with fixed costs
    for (int i = 0; i < 71; ++i) {
        goals.push_back(std::make_unique<Goal>(i));
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
    // REMOVE LATER
    if (criterionMap.find(criterionId) == criterionMap.end()) {
        return false;
    }

    const auto& [adjCriteria, adjGoals] = criterionMap.at(criterionId);

    // Check if no one owns adjacent criteria
    for (int adj : adjCriteria) {
        const auto& criterion = criteria[adj];
        if (!criterion->getOwnerName().empty()) {
            return false;
        }
    }

    // Check if the student owns at least one adjacent goal
    for (int adj : adjGoals) {
        const auto& goal = goals[adj];
        if (goal->getOwnerName() == student.getColour()) {
            return true;
        }
    }

    return false;
}

bool Board::emptyAdjacent(int criterionId) const {
    const auto& [adjCriteria, adjGoals] = criterionMap.at(criterionId);
    for (int adj : adjCriteria) {
        const auto& criterion = criteria[adj];
        if (!criterion->getOwnerName().empty()) {
            return false;
        }
    }
    return true;
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
            switch (tiles[tileIndex]->getType())
            {
            case Resource::CAFFEINE:
                cout << "CAFFEINE";
                break;
            case Resource::STUDY:
                cout << "STUDY";
                break;
            case Resource::LAB:
                cout << "LAB";
                break;
            case Resource::TUTORIAL:
                cout << "TUTORIAL";
                break;
            default:
                cout << "NETFLIX";
                break;
            }
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