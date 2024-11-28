#include "resource.h"

#include <iostream>

// Converts string to Resource
Resource resourceFromInt(std::string s) {
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
        default:
            return "NETFLIX";
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