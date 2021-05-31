// T05_G02

#include "gate.h"

Gate::Gate(const Position &position)
{
    this->position = position;
}

/******************************************************************************/

Position Gate::getPosition() const
{
    return position;
}