#include "goal.h"

Goal::Goal(int id, std::shared_ptr<Student> owner, bool achieved):
    Achievement{id, owner},
    achieved{achieved}
{
    upgradeCost = {
        {Resource::STUDY, 1},
        {Resource::TUTORIAL, 1}
    };
}

const std::map<Resource, int>& Goal::getUpgradeCost() const {
    return upgradeCost;
}

Goal::~Goal() {}
