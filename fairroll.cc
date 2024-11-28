#include "fairroll.h"
#include <random>

// FairRoll constructor
FairRoll::FairRoll(std::mt19937& gen) : gen{gen} {}

// Roll method
int FairRoll::roll() const {
    std::uniform_int_distribution<> distrib{1, 6}; // Range between 1 and 6 (inclusive)
    int rollSum = 0;

    // First roll
    rollSum += distrib(gen);
    // Second roll
    rollSum += distrib(gen);

    // Return sum of rolls
    return rollSum;
}
