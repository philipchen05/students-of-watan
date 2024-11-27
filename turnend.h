#ifndef TURNEND_H
#define TURNEND_H

// TurnEnd class for managing end of player turn
class TurnEnd: public Turn {
    private:
        void board(); // Display board
        void status(); // Print status of each student in order of student index
        void criteria(); // Print current student's criteria
        void achieve(int id); // Achieve goal
        void complete(int id); // Complete criterion
        void improve(int id); // Improve criterion
        boolean canAfford(Achievement* a); // Determine if player can afford desired goal/achievement
        void purchase(Achievement* a) // Deducts cost of given achievement from player resources
        void trade(string colour, string give, string take); // Trade resources with another player
        void help(); // Print help guide
    public:
        TurnEnd(Student* player); // TurnEnd constructor
        virtual ~TurnEnd() = default; // TurnEnd destructor
        void play() override; // Method for playing end of turn events
};

#endif
