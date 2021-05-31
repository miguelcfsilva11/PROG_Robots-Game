// T05_G02

#ifndef ROBOT_H
#define ROBOT_H

#include "movement.h"

class Robot{

public:

    enum State { ALIVE, STUCK, DEAD };

    /**
     * Class Constructor
     *
     * @param position A Position struct representing the robot's coordinates in the maze 
     */
    Robot(const Position &position);

    int getID() const;
    char getSymbol() const;
    int getRow() const;
    int getCol() const;
    void setRow(int row);
    void setCol(int col);
    Position getPosition() const;
    bool isAlive() const;

    /**
     * For every located robot, compare its
     * position to the human's and find
     * the most efficient path that leads to him.
     *
     * @param playerPos the human's position
     */
    void seekHuman(const Position &player_pos);

    void setPosition(const Position &pos);
    void setAsDead();

private:

    static int robotCounter;
    int id;
    char symbol;
    Position position;
    bool alive;
};

#endif