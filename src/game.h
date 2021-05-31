// T05_G02

#ifndef GAME_H
#define GAME_H

#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <map>

#include "maze.h"
#include "robot.h"
#include "player.h"
#include "movement.h"
#include "input.h"


using namespace std;

class Game {
public:

    /**
     * Class Constructor
     *
     * @param filename A string that holds information on which maze should be loaded
     */
    Game(const string &filename);


    /**
     * Main game loop: while the user is alive,
     * keep asking for input that represents the
     * direction the user wants to move to.
     *
     * @return true if the player wins
     * @return false if the player loses
     */
    bool play();


    /**
     * Inspects whether the position the player 
     * desires to move to is occupied by either a 
     * dead robot or a non-electrified fence.
     *
     * @param direction A char that represents the direction the user is trying to move to
     *
     * @return true if the player moves to a valid spot, even when causing his death
     * @return false if he moves to the place of one of the objects above
     */
    bool validMove(char direction);


    /**
     * Compares the player's position to the location
     * of the maze's exit gate, and checks whether he
     * has reached it or not.
     *
     * @return true if the player has reached the gate
     * @return false if otherwise
     */
    bool reachedGate();

private:

    /**
     * Fills an two dimensional array of chars and
     * prints out to the terminal the current state
     * of the maze (including all objects)
     *
     * @return
     */
    void showGameDisplay() const;


    /**
     * Checks if an given robot has collided with any fence
     * there is left on the maze, causing his death.
     *
     * @param robot A functioning robot there is still on the maze
     * @param Posts A vector of Post objects that are present in the maze
     *
     * @return true if it collides with any of them
     * @return false if otherwise
     */
    bool collide(Robot &robot, Post& Post);


    /**
     * Checks if the player has collided with any fence
     * there is left on the maze, causing his death.
     *
     * @param player The human there is on the maze
     * @param Posts A vector of Post objects that are present in the maze
     *
     * @return true if he collides with any of them
     * @return false if otherwise
     */
    bool collide(Player &player, vector<Post>& Posts); 


    /**
     * Checks if an given robot has collided with the player
     *
     * @param robot A functioning robot there is still on the maze
     * @param player The human there is on the maze
     *
     * @return true if the robot has collided with the human
     * @return false if otherwise
     */
    bool collide(Robot &robot, Player& player);


    /**
     * Checks if an given robot has collided with another robot
     *
     * @param firstRobot A functioning robot there is still on the maze
     * @param secondRobot A functioning robot there is still on the maze
     *
     * @return true if the robot has collided with the robot
     * @return false if otherwise
     */
    bool collide(Robot &firstRobot, Robot &secondRobot);


    Maze maze;
    Player player;
    vector<Robot> robots; 
};

#endif