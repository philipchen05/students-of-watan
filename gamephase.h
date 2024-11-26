#ifndef GAMEPHASE_H
#define GAMEPHASE_H

#include <memory>

class Game;

// GamePhase abstract class
class GamePhase {
    protected:
        Game* game; // Pointer to Game object
    public:
        GamePhase(Game* game); // GamePhase constructor
        virtual ~GamePhase() = default; // GamePhase destructor
        virtual void play() = 0; // Method for executing game phase events
};

#endif
