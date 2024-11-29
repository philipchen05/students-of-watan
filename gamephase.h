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
        virtual bool getPlayAgain() const; // Return whether or not players wish to play again
        void save(std::string file, Student* player); // saves to the file
};

#endif
