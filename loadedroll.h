#ifndef LOADEDROLL_H
#define LOADEDROLL_H

#include "diceroll.h"

// LoadedRoll class for loaded dice roll algorithm
class LoadedRoll: public DiceRoll {
    public:
        int roll() override; // Roll method
};

#endif
