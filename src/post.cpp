// T05_G02

#include "post.h"

Post::Post(const Position &position, char type)
{
    this->position = position;
    this->type = type;
}

/******************************************************************************/

int Post::getRow() const
{
    return position.row;
}

/******************************************************************************/

int Post::getCol() const
{
    return position.col;
}

/******************************************************************************/

char Post::getSymbol() const
{
    return type;
}

/******************************************************************************/

bool Post::isElectrified() const
{
    if(type == '*')
        return true;
    else
        return false;
}

/******************************************************************************/

Position Post::getPosition() const
{
    return position;
}