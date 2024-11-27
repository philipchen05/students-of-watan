#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <string>

enum class Resource {
    CAFFEINE = 0,
    LAB,
    LECTURE,
    STUDY,
    TUTORIAL,
    NETFLIX,
};

// Converts string to Resource
Resource resource(std::string s) {
    if(s == "CAFFEINE") {
        return Resource::CAFFEINE;
    } else if(s == "LAB") {
        return Resource::LAB;
    } else if(s == "LECTURE") {
        return Resource::LECTURE;
    } else if(s == "STUDY") {
        return Resource::STUDY;
    } else if(s == "TUTORIAL") {
        return Resource::TUTORIAL;
    } else {
        return Resource::NETFLIX;
    }
}

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
