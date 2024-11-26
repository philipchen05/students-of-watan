#include "achievement.h"
#include "student.h"

Achievement::Achievement(int id, std::shared_ptr<Student> owner):
    Observer{},
    id{id},
    owned{(owner != nullptr)}, // true if given student instance
    owner{owner}
{}

// true if achievement has owner, otherwise false
bool Achievement::isOwned() const {
    return owned;
}

// if achievement is owned, returns owner's colour, otherwise empty string
const std::string& Achievement::getOwnerName() const {
    if (owner != nullptr) return owner->getColour();
    return std::string{};
}

// returns achievement's id number
int Achievement::getId() const {
    return id;
}

Achievement::~Achievement() {}
