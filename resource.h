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
Resource resourceFromString(std::string s);

// Converts int to Resource
Resource resourceFromInt(int value);

// Converts Resource to string
std::string resourceToString(Resource type);

// Converts Resource to int
int resourceToInt(Resource type);

// Overloaded operator<< method for outputting Resource types
std::ostream &operator<<(std::ostream &out, const Resource &r);

#endif
