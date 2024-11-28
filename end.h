#ifndef END_H
#define END_H

#include "gamephase.h"

// End class for managing end of game
class End: public GamePhase {
    private:
        bool playAgain; // Whether or not players wish to play again
    public:
        End(Game* game); // End constructor
        ~End() = default; // End destructor
        void play() override; // Method for executing end of game events
        bool getPlayAgain() const; // Getter method for playAgain
};

#endif
