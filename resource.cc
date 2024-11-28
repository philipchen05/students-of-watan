#include "resource.h"

#include <iostream>

// Converts string to Resource
Resource resourceFromString(std::string s) {
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

// Converts string to Resource
Resource resourceFromInt(int value) {
    if(value == 0) {
        return Resource::CAFFEINE;
    } else if (value == 1) {
        return Resource::LAB;
    } else if(value == 2) {
        return Resource::LECTURE;
    } else if(value == 3) {
        return Resource::STUDY;
    } else if(value == 4) {
        return Resource::TUTORIAL;
    } else {
        return Resource::NETFLIX;
    }
}

std::string resourceToString(Resource type) {
    switch (type)
    {
        case Resource::CAFFEINE:
            return "CAFFEINE";
        case Resource::STUDY:
            return "STUDY";
        case Resource::LAB:
            return"LAB";
        case Resource::TUTORIAL:
            return "TUTORIAL";
        case Resource::LECTURE:
            return "LECTURE";
        default:
            return "NETFLIX";
    }
}

int resourceToInt(Resource type) {
    switch (type)
    {
        case Resource::CAFFEINE:
            return 0;
        case Resource::LAB:
            return 1;
        case Resource::LECTURE:
            return 2;
        case Resource::STUDY:
            return 3;
        case Resource::TUTORIAL:
            return 4;
        default:
            return 5;
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