#include "student.h"
#include "resource.h"
#include "criterion.h"

#include <iostream>
#include <map>

Student::Student(std::string colour, int number, int numVP, const std::map<Resource, int> &resources):
    colour{colour},
    number{number},
    numVP{numVP},
    resources{resources}
{}

bool Student::canAcquire(Achievement *a) {
    std::map<Resource, int> cost = a->getUpgradeCost(); // get cost of upgrading

    // check that student has enough of each resource needed
    for(auto &[resource, needed]: cost) {
        if (resources[resource] < needed) {
            return false;
        }
    }
    return true;
}

void Student::complete(Criterion *c) {
    if (!canAcquire(c)) {
        std::cout << "You do not have enough resources." << std::endl;
    }
}

void Student::addResources(Resource type, int amount) {
    resources[type] += amount;
}

std::string Student::getColour() const {
    return colour;
}

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

void Student::printCriteria() const {
    std::cout << colour << " has completed:" << std::endl;
    for (auto criterion: criteria) {
        std::cout << "\t" << criterion->getId() << " " << criterion->getCompletion() << std:: endl;
    }
}

Student::~Student() {}