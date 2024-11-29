#include "student.h"
#include "resource.h"
#include "criterion.h"
#include "goal.h"

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <cmath>
#include <stdexcept>

const std::map<Resource, int> Student::defaultResources = {
    {Resource::CAFFEINE, 0},
    {Resource::LAB, 0},
    {Resource::LECTURE, 0},
    {Resource::TUTORIAL, 0},
    {Resource::STUDY, 0}
};

// Constructor
Student::Student(std::string colour, int number, const std::map<Resource, int> &resources, 
                std::vector<Criterion*> criteria, std::vector<Goal*> goals):
    colour{colour},
    number{number},
    resources{resources},
    criteria{criteria},
    goals{goals}
{}

// adds criterion to student's list of completed criteria
void Student::addCriterion(Criterion *c) {
    // quit if criterion already tracked by student
    for (Criterion* sptr: criteria) {
        if (sptr == c) {
            std::cout << colour << " already has criterion " << c->getId() << std::endl;
            return;
        }
    }

    // add ptr of criterion to student's list of criteria
    criteria.emplace_back(c);
}

// adds goal to student's list of achieved goals
void Student::addGoal(Goal *g) {
    // quit if goal already tracked by student
    for (Goal* sptr: goals) {
        if (sptr == g) {
            std::cout << colour << " already has criterion " << g->getId() << std::endl;
            return;
        }
    }

    // add ptr of goal to student's list of goals
    goals.emplace_back(g);
}

void Student::addResources(Resource type, int amount) {
    resources[type] += amount;
}

// removes specified amount of the specified resource
void Student::removeResources(Resource type, int amount) {
    resources[type] = std::max(resources[type] - amount, 0); // can't have negative resources
}

// returns student's colour (name)
const std::string& Student::getColour() const {
    return colour;
}

// returns student's current resources
const std::map<Resource, int>& Student::getResources() const {
    return resources;
}

// returns the number of resources of the given type
int Student::getResource(Resource type) const {
    return resources.at(type);
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
    data += std::to_string(resources.at(Resource::CAFFEINE)) + " ";
    data += std::to_string(resources.at(Resource::LAB)) + " ";
    data += std::to_string(resources.at(Resource::LECTURE)) + " ";
    data += std::to_string(resources.at(Resource::STUDY)) + " ";
    data += std::to_string(resources.at(Resource::TUTORIAL)) + " ";

    // add goals
    data += "g ";
    for (auto goalSPtr: goals) {
        data += std::to_string(goalSPtr->getId()) + " ";
    }

    // add criteria
    data += "c ";
    for (size_t i = 0; i < criteria.size(); ++i) {
        data += std::to_string(criteria[i]->getId()) + " " + std::to_string(criteria[i]->getCompletion());
        if (i != criteria.size() - 1) data += " ";
    }

    return data;
}

// prints student's status (victory points and resources)
void Student::printStatus() const {
    // .at used because [] operator has no const overload
    try {
        std::cout << colour << " has " 
            << getVP() << " victory points, " 
            << getResource(Resource::CAFFEINE) << " caffeines, "
            << getResource(Resource::LAB) << " labs, "
            << getResource(Resource::LECTURE) << " lectures, "
            << getResource(Resource::TUTORIAL) << " tutorials, and "
            << getResource(Resource::STUDY) << " studies."
            << std::endl;
    } catch(std::exception &e) {
        std::cerr << "Failed to print Student " << getColour() << "'s status: " << std::endl;
        std::cerr << "\t" << e.what() << std::endl;
    }
}

// prints student's completed criteria
void Student::printCriteria() const {
    std::cout << colour << " has completed:" << std::endl;
    for (auto criterion: criteria) {
        std::cout << criterion->getId() << " " << criterion->getCompletion() << std:: endl;
    }
}

// returns number of victory points
int Student::getVP() const {
    int numVP = 0;
    for (Criterion* c: criteria) {
        numVP += c->getCompletion();
    }
    return numVP;
}

Student::~Student() {}
