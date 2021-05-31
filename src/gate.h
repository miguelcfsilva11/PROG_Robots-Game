// T05_G02

#ifndef GATE_H
#define GATE_H


#include "movement.h"

class Gate {
public:

    /**
     * Class Constructor
     *
     * @param position A Position struct representing the gate's coordinates in the maze 
     */
    Gate(const Position &position);

    
    Position getPosition() const;

private:
    Position position;
};

#endif