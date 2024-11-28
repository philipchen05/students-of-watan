#include "gamephase.h"

// GamePhase constructor
GamePhase::GamePhase(Game* game) : game{game} {}

bool GamePhase::getPlayAgain() const {
    return false;
}
