#include "achievement.h"
#include "student.h"

Achievement::Achievement(int id, std::shared_ptr<Student> owner):
    Observer{},
    id{id},
    owner{owner}
{}

std::string Achievement::getOwnerName() const {
    return owner->getColour();
}

int Achievement::getId() const {
    return id;
}

Achievement::~Achievement() {}
