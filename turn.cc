#include "turn.h"
#include "student.h"

Turn::Turn(Game* game, Student* player) : GamePhase{game}, player{player} {}

Student* Turn::getPlayer() {
    return player;
}