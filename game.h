#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>

class Game {
    private:
        std::unique_ptr<Board> board;
        std::vector<std::shared_ptr<Student>> players;
        std::unique_ptr<GamePhase> gamePhase;

    public:
        Game(); // Game constructor
        void play(); // Method for playing game
};

#endif
