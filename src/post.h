// T05_G02

#ifndef POST_H
#define POST_H


#include "movement.h"

class Post {
public:

    /**
     * Class Constructor
     *
     * @param position A Position struct representing the post's coordinates in the maze
     * @param type specifies whether a fence is electrified or not
     */
    Post(const Position &position, char type);
    
    int getRow() const;
    int getCol() const;
    Position getPosition() const;
    char getSymbol() const;
    bool isElectrified() const;

private:

    Position position;
    char type;
};

#endif