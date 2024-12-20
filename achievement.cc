#include "achievement.h"
#include "student.h"

#include <iostream>

Achievement::Achievement(int id, Student* owner):
    Observer{},
    id{id},
    owner{owner}
{}

void Achievement::notify(const Subject *sbj) {}

// true if achievement has owner, otherwise false
bool Achievement::isOwned() const {
    return owner != nullptr;
}

// if achievement is owned, returns owner's colour, otherwise empty string
std::string Achievement::getOwnerName() const {
    if (owner != nullptr) return owner->getColour();
    return std::string{};
}

// returns achievement's id number
int Achievement::getId() const {
    return id;
}

Achievement::~Achievement() {}
