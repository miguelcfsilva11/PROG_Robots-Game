// T05_G02

#include "player.h"

Player::Player()

{
    this->position.row = 1;
    this->position.col = 1;
    this->symbol = 'H';

}

/******************************************************************************/

Player::Player(const Position &position)

{
    this->position = position;
    this->symbol = 'H';

}

/******************************************************************************/

int Player::getRow() const {

    return position.row;

}

/******************************************************************************/

int Player::getCol() const {

    return position.col;

}

/******************************************************************************/

char Player::getSymbol() const {

    return symbol;

}

/******************************************************************************/

bool Player::isAlive() const {

    if (alive) {
        return true;
    }
    else {
        return false;
    }
}

<<<<<<< HEAD
/******************************************************************************/

void Player::setAsDead(){

    alive = false;
    symbol = 'h';

}

/******************************************************************************/

void Player::move(Movement delta){

    position.row += delta.dRow;
    position.col += delta.dCol;
    

}

/******************************************************************************/

Position Player::getPosition() const{
    return position;
=======
void Player::setAsDead(){

    alive = false;

}

void Player::move(Movement delta){

    row += delta.dRow;
    col += delta.dCol;
    

>>>>>>> 649420752986f47fb27dfa733101822274c3a6e9
}