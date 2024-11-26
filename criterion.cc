#include "criterion.h"
#include "observer.h"
#include "tile.h"

Criterion::Criterion(int id, std::shared_ptr<Student> owner, CompletionLevel completion):
    Achievement{id, owner},
    completion{completion}
{
    // maps CURRENT level to cost of NEXT level
    upgradeCost = {
        {CompletionLevel::INCOMPLETE, 
            {
                {Resource::CAFFEINE, 1},
                {Resource::LAB, 1},
                {Resource::LECTURE, 1},
                {Resource::TUTORIAL, 1}
            }
        },
        {CompletionLevel::ASSIGNMENT, 
            {
                {Resource::LECTURE, 2},
                {Resource::STUDY, 3}
            }
        },
        {CompletionLevel::MIDTERM, 
            {
                {Resource::CAFFEINE, 3},
                {Resource::LAB, 2},
                {Resource::LECTURE, 2},
                {Resource::TUTORIAL, 1},
                {Resource::STUDY, 2}
            }
        },
    };
}

// updates resources of owner
void Criterion::notify(const Subject *sbj) {
    const Tile *t = dynamic_cast<const Tile*>(sbj);
    owner->addResources(t->getType(), (int)this->completion); // add resources to owner
}

int Criterion::getCompletion() const {
    return (int)completion;
}
const std::map<Resource, int>& Criterion::getUpgradeCost() const {
    return upgradeCost.at(completion); // use .at because [] doesn't have overload for const map
}

Criterion::~Criterion() {}
