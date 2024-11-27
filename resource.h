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
            out << "CAFFEINE";
            break;
        case Resource::LAB:
            out << "LAB";
            break;
        case Resource::LECTURE:
            out << "LECTURE";
            break;
        case Resource::STUDY:
            out << "STUDY";
            break;
        case Resource::TUTORIAL:
            out << "TUTORIAL";
            break;
        case Resource::NETFLIX:
            out << "NETFLIX";
            break;
    }
    return out;
}

#endif
