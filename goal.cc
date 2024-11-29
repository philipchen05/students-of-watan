#include "goal.h"
#include "resource.h"

#include <iostream>

const std::map<Resource, int> Goal::upgradeCost = {
    {Resource::STUDY, 1},
    {Resource::TUTORIAL, 1}
};

Goal::Goal(int id, Student* owner, bool achieved):
    Achievement{id, owner},
    achieved{achieved}
{}

// sets goal as achieved by the given student
void Goal::achieve(Student* s) {
    if (owner != nullptr) {
        std::cout << getOwnerName() << " has already completed goal " << getId() << std::endl;
        return;
    }
    owner = s;
    achieved = true;
}

const std::map<Resource, int>& Goal::getUpgradeCost() const {
    return upgradeCost;
}

Goal::~Goal() {}
