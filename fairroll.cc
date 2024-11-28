#include "fairroll.h"
#include <random>

// FairRoll constructor
FairRoll::FairRoll(int seed) : gen{seed} {}

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
