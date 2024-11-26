#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>

enum class Resource {
    CAFFEINE = 0,
    LAB,
    LECTURE,
    STUDY,
    TUTORIAL,
    NETFLIX,
};

// Overloaded operator<< method for outputting Resource types
std::ostream &operator<<(std::ostream &out, const Resource &r) {
    switch(r) {
        case Resource::CAFFEINE:
            out << "Caffeine";
            break;
        case Resource::LAB:
            out << "Lab";
            break;
        case Resource::LECTURE:
            out << "Lecture";
            break;
        case Resource::STUDY:
            out << "Study";
            break;
        case Resource::TUTORIAL:
            out << "Tutorial";
            break;
        case Resource::NETFLIX:
            out << "Netflix";
            break;
    }
    return out;
}

#endif
