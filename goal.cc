#include "goal.h"
#include "resource.h"

const std::map<Resource, int> Goal::upgradeCost = {
    {Resource::STUDY, 1},
    {Resource::TUTORIAL, 1}
};

Goal::Goal(int id, std::shared_ptr<Student> owner, bool achieved):
    Achievement{id, owner},
    achieved{achieved}
{
}

const std::map<Resource, int>& Goal::getUpgradeCost() const {
    return upgradeCost;
}

Goal::~Goal() {}
