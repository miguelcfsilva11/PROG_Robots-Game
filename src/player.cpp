#include "movement.h"

class Player {

public:

    Player(int row, int col, char symbol);
    int getRow() const;
    int getCol() const;
    char getSymbol() const;
    bool isAlive() const;
    void setAsDead();
    void move(Movement delta);

private:

    int row, col;
    bool alive;
    char symbol;

};


Player::Player(int row, int col, char symbol)

{
    this->row = row;
    this->col = col;
    this->symbol = symbol;

}

int Player::getRow() const {

    return row;

}

int Player::getCol() const {

    return col;

}

char Player::getSymbol() const {

    return symbol;

}

bool Player::isAlive() const {

    if (alive) {
        return true;
    }
    else {
        return false;
    }
}

void Player::setAsDead(){

    alive = false;

}

void Player::move(Movement delta){

    row += delta.dRow;
    col += delta.dCol;
    

}