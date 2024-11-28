#ifndef DICE_H
#define DICE_H

// Dice class
class Dice {
    private:
        int seed; // Seed for random number generation
    public:
        Dice(int seed); // Dice constructor
        ~Dice() = default; // Dice destructor
        int roll(bool fair) const; // Dice roll method
};

#endif
