#include "student.h"
#include "resource.h"
#include "criterion.h"
#include "goal.h"

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <cmath>

// Constructor
Student::Student(std::string colour, int number, int numVP, const std::map<Resource, int> &resources):
    colour{colour},
    number{number},
    numVP{numVP},
    resources{resources}
{}

// adds criterion to student's list of completed criteria
void Student::addCriterion(Criterion *c) {
    // quit if criterion already tracked by student
    for (std::shared_ptr<Criterion> sptr: criteria) {
        if (sptr.get() == c) {
            std::cout << colour << " already has criterion " << c->getId() << std::endl;
            return;
        }
    }

    // add shared ptr of criterion to student's list of criteria
    std::shared_ptr<Criterion> cptr{c}; // make shared ptr
    criteria.emplace_back(cptr); // add to list
}

// adds goal to student's list of achieved goals
void Student::addGoal(Goal *g) {
    // quit if goal already tracked by student
    for (std::shared_ptr<Goal> sptr: goals) {
        if (sptr.get() == g) {
            std::cout << colour << " already has criterion " << g->getId() << std::endl;
            return;
        }
    }

    // add shared ptr of goal to student's list of goals
    std::shared_ptr<Goal> gptr{g}; // make shared ptr
    goals.emplace_back(gptr); // add to list
}

void Student::addResources(Resource type, int amount) {
    resources[type] += amount;
}

// removes specified amount of the specified resource
void Student::removeResources(Resource type, int amount) {
    resources[type] = std::max(resources[type] - amount, 0); // can't have negative resources
}

// adds the specified amount of victory points
void Student::addVP(int amount) {
    numVP += amount;
}

// returns student's colour (name)
const std::string& Student::getColour() const {
    return colour;
}

// returns student's current resources
const std::map<Resource, int>& Student::getResources() const {
    return resources;
}

// returns total number of resources
int Student::getTotalResources() const {
    int sum = 0;
    for (auto &[resource, amount]: resources) {
        sum += amount;
    }
    return sum;
}

// returns string with all student data to be saved to file
std::string Student::getData() const {
    std::string data = "";

    // add all resources
    for (auto &[resource, amount]: resources) {
        data += std::to_string(amount) + " ";
    }

    // add goals
    data += "g ";
    for (auto goalSPtr: goals) {
        data += std::to_string(goalSPtr->getId()) + " ";
    }

    // add criteria
    data += "c ";
    for (auto criterionSPtr: criteria) {
        data += std::to_string(criterionSPtr->getId()) + " " + std::to_string(criterionSPtr->getCompletion());
    }

    return data;
}

// prints student's status (victory points and resources)
void Student::printStatus() const {
    // .at used because [] operator has no const overload
    std::cout << colour << " has " 
        << numVP << " victory points, " 
        << resources.at(Resource::CAFFEINE) << " caffeines, "
        << resources.at(Resource::LAB) << " labs, "
        << resources.at(Resource::LECTURE) << " lectures, "
        << resources.at(Resource::TUTORIAL) << " tutorials, and"
        << resources.at(Resource::STUDY) << " studies."
        << std::endl;
}

// prints student's completed criteria
void Student::printCriteria() const {
    std::cout << colour << " has completed:" << std::endl;
    for (auto criterion: criteria) {
        std::cout << "\t" << criterion->getId() << " " << criterion->getCompletion() << std:: endl;
    }
}

Student::~Student() {}