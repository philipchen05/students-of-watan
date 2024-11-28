#include "dice.h"
#include "fairroll.h"
#include "loadedroll.h"
#include <memory>

// Dice constructor
Dice::Dice(int seed) : seed{seed} {}

int Dice::roll(bool fair) const {
    std::unique_ptr<DiceRoll> dr; // Unique pointer to DiceRoll object

    // If fair is true, initialize dr as a FairRoll object;
    // otherwise initialize as a LoadedRoll object
    if(fair) {
        dr = std::make_unique<FairRoll>(seed);
    } else {
        dr = std::make_unique<LoadedRoll>();
    }

    return dr->roll(); // Return rolled value; note roll() is polymorphic
}
