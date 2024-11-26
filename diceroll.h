#ifndef DICEROLL_H
#define DICEROLL_H

// DiceRoll abstract class for dice roll algorithm
class DiceRoll {
    public:
        virtual ~DiceRoll() = default; // virtual DiceRoll destructor
        virtual int roll() const = 0; // Roll method
};

#endif
