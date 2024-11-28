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
Resource resourceFromInt(std::string s);

Resource resourceFromInt(int value);

// Overloaded operator<< method for outputting Resource types
std::ostream &operator<<(std::ostream &out, const Resource &r);

#endif
