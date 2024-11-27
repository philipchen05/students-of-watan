#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <cctype>

enum class Resource {
    CAFFEINE = 0,
    LAB,
    LECTURE,
    STUDY,
    TUTORIAL,
    NETFLIX,
};

// Converts string to Resource
Resource resource(string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::toupper(c); });
    switch(s) {
        case "CAFFEINE":
            return Resource::CAFFEINE;
        case "LAB":
            return Resource::LAB;
        case "LECTURE":
            return Resource::LECTURE;
        case "STUDY":
            return Resource::STUDY;
        case "TUTORIAL":
            return Resource::TUTORIAL;
        case "NETFLIX":
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
