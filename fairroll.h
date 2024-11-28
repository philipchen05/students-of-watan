#ifndef FAIRROLL_H
#define FAIRROLL_H

#include "diceroll.h"
#include <random>

// FairRoll class for fair dice roll algorithm
class FairRoll: public DiceRoll {
    private:
        std::mt19937 gen; // Random number generator
    public:
        FairRoll(int seed); // FairRoll constructor
        int roll() override; // Roll method
};

#endif
