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
    std::cerr << "Criterion::complete() - setting onwer = " << s << std::endl; // DEBUG - MUST DELETE
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
    std::cerr << *this << " entered notify()" << std::endl; // DEBUG - MUST DELTE
    const Tile *tile = dynamic_cast<const Tile*>(sbj);
    std::cerr << "\tcasted subject to tile" << std::endl;// DEBUG - MUST DELTE
    // if criterion has been completed, add resources to its owner
    if (isOwned()) {
        owner->addResources(tile->getType(), getCompletion());
        std::cerr << "\tadded resources to owner" << std::endl;// DEBUG - MUST DELTE
    } else {
        std::cerr << "\thas no owner! doing nothing" << std::endl;
    }
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

// prints criterion contents for debug [Criterion: (id: ID, isOwned: ISOWNED, owner: OWNER, comp: COMPLETIONLEVEL)]
std::ostream& operator<<(std::ostream &out, const Criterion &criterion) {
    out << "[Criterion: (id: " << criterion.getId() << " , isOwned: " << criterion.isOwned() << ", owner: " << criterion.getOwnerName() << ", comp: " << criterion.getCompletion() << ")]";
    return out;
}