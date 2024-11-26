#include "fairroll.h"
#include <random>

// Roll method
int FairRoll::roll() {
    std::random_device rd; // Generate non-deterministic seed
    std::mt19937 gen{rd()}; // Initialize random number generator with seed
    std::uniform_int_distribution<> distrib{1, 6}; // Range between 1 and 6 (inclusive)
    int rollSum = 0;

    // First roll
    rollSum += distrib(gen);
    // Second roll
    rollSum += distrib(gen);

    // Return sum of rolls
    return rollSum;
}
