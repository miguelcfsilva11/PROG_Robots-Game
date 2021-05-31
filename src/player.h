// T05_G02

#ifndef PLAYER_H
#define PLAYER_H

#include "movement.h"

class Player {

public:

    /**
     * Default Player constructor.
     */
    Player();


    /**
     * Class Constructor
     *
     * @param position A Position struct representing the player's coordinates in the maze 
     */
    Player(const Position &position);
    int getRow() const;
    int getCol() const;
    char getSymbol() const;
    bool isAlive() const;
    void setAsDead();
    Position getPosition() const;
    void move(Movement delta);

private:

    Position position;
    bool alive;
    char symbol;

};

#endif