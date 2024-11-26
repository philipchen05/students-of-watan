#ifndef END_H
#define END_H

#include <gamephase.h>

// End class for managing end of game
class End: public GamePhase {
    private:
        boolean playAgain; // Whether or not players wish to play again
    public:
        End(); // End constructor
        ~End() = default; // End destructor
        void play() override; // Method for executing end of game events
        boolean playAgain(); // Getter method for playAgain
};

#endif
