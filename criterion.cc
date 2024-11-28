#include "criterion.h"
#include "achievement.h"
#include "observer.h"
#include "tile.h"

#include <iostream>

const std::map<Criterion::CompletionLevel, std::map<Resource, int>> Criterion::upgradeCosts = {
    {Criterion::CompletionLevel::INCOMPLETE, 
        {
            {Resource::CAFFEINE, 1},
            {Resource::LAB, 1},
            {Resource::LECTURE, 1},
            {Resource::TUTORIAL, 1}
        }
    },
    {Criterion::CompletionLevel::ASSIGNMENT, 
        {
            {Resource::LECTURE, 2},
            {Resource::STUDY, 3}
        }
    },
    {Criterion::CompletionLevel::MIDTERM, 
        {
            {Resource::CAFFEINE, 3},
            {Resource::LAB, 2},
            {Resource::LECTURE, 2},
            {Resource::TUTORIAL, 1},
            {Resource::STUDY, 2}
        }
    },
};

Criterion::Criterion(int id, Student* owner, CompletionLevel completion):
    Achievement{id, owner},
    completion{completion}
{}

// makes criterion completed by the given student (which becomes criterion's owner)
void Criterion::complete(Student* s) {
    if (owner != nullptr) {
        std::cout << getOwnerName() << " has already completed criterion " << getId() << std::endl;
        return;
    }
    owner = s;
    completion = Criterion::CompletionLevel::ASSIGNMENT;
}

// upgrades criterion to the next completion level (e.g. assignment to midterm)
void Criterion::improve() {
    switch (completion) {
    case Criterion::CompletionLevel::ASSIGNMENT:
        completion = Criterion::CompletionLevel::MIDTERM;
        break;
    case Criterion::CompletionLevel::MIDTERM:
        completion = Criterion::CompletionLevel::EXAM;
        break;
    default:
        std::cout << "Invalid improvement of criterion " << getId() << " with completion level " << getCompletion() << std::endl;
        break;
    }
}

// adds resources earned from the notifying tile to the owner
void Criterion::notify(const Subject *sbj) {
    const Tile *tile = dynamic_cast<const Tile*>(sbj);
    owner->addResources(tile->getType(), getCompletion());
}

// returns an integer [0,3] representing completion level
int Criterion::getCompletion() const {
    return (int)completion;
}

// returns the cost of upgrading to next level
const std::map<Resource, int>& Criterion::getUpgradeCost() const {
    return upgradeCost.at(completion); // use .at because [] doesn't have overload for const map
}

Criterion::~Criterion() {}
