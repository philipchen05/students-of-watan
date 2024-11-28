#ifndef DICE_H
#define DICE_H

#include <random>

// Dice class
class Dice {
    private:
        std::mt19937 &gen; // Random number generator
    public:
        Dice(std::mt19937 &gen); // Dice constructor
        ~Dice() = default; // Dice destructor
        int roll(bool fair) const; // Dice roll method
};

#endif
