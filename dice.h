#ifndef DICE_H
#define DICE_H

// Dice class
class Dice {
    public:
        Dice() = default; // Dice constructor
        ~Dice() = default; // Dice destructor
        int roll(bool fair) const; // Dice roll method
};

#endif
