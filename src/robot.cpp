#include "movement.h"

class Robot{
public:
    enum State { ALIVE, STUCK, DEAD };
    Robot(int row, int col);
    int getID() const;
    char getSymbol() const; // get char representation of robot (R if alive, r if dead)
    int getRow() const;
    int getCol() const;
    Position getPosition() const;
    bool isAlive() const;
    void setRow(int x);
    void setCol(int y);
    void setPosition(const Position &pos);
    void setAsDead();
private:
    static int robotCounter; //used to attribute automatically the id to the robots
    int id;
    int row, col;
    bool alive;
};

Robot::Robot(int row, int col)
{
    this->row = row;
    this->col = col;
}

int Robot::getID() const
{
    return id;
}

char Robot::getSymbol() const
{
    if(alive)
        return 'R';
    else
        return 'r';
}

int Robot::getRow() const
{
    return row;
}

int Robot::getCol() const
{
    return col;
}

Position Robot::getPosition() const
{
    Position pos = { row, col };
    return pos;
}

bool Robot::isAlive() const
{
    if(alive)
        return true;
    else
        return false;
}

void Robot::setRow(int x)
{
    row = x;
}

void Robot::setCol(int y)
{
    col = y;
}

void Robot::setPosition(const Position &pos)
{
    row = pos.row;
    col = pos.col;
}

void Robot::setAsDead()
{
    alive = false;
}