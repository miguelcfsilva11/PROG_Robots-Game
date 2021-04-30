#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "game.h"
#include "robots.h"
using namespace std;

/******************************************************************************/

/**
* Looks for human's position on the maze and stores it.
*
* @return pair of integers with his coordinates.
*/
pair <int, int> findHuman (vector<string>& maze)
{

    int human_row, human_col; // Human's coordinates.
    bool humanFound = false;

    for(int row = 0; row < maze.size(); row++){
        for(int col = 0; col < maze[row].size(); col++){
            if (maze[row][col] == 'H'){
                
                // If we find the human, store his
                // location in the following variables
                // and update humanFound's value.

                humanFound = true;

                human_row = row;
                human_col = col;
                break;

            }
        }
    }

    if (!humanFound)
        return make_pair(-1,-1);
    else
        return make_pair(human_row, human_col);
}

/******************************************************************************/

/**
* Checks whether the player is alive by evaluating 
* his surroundings. In case he's in contact with either
* a robot or a fence, then we must declare him dead.
* 
* @return true if the human is safe.
* @return false in case he moved to the place of either a robot or a fence.
*/
bool isAlive(vector<string>& maze)
{
    // Retrieve human's coordinates.

    int human_row, human_col;
    human_row =  findHuman(maze).first;
    human_col =  findHuman(maze).second;

    if (human_row == -1 && human_col == -1)

    {

        // In case our human has been captured by the remanining robots
        // the 'findHuman' function returns the pair (-1, -1). In those
        // circumstances, we must declare our player as dead.

        return false;
    }

    return true;
}

/******************************************************************************/

/**
* If possible, updates the coordinates
* of the player, acording to the
* direction chosen by the user.
*
* @param maze A vector containing information regarding the maze.
* @param key A character which determines the direction the user is trying to move.
*
* @return false if the user moves to the place of an eletric fence or robot.
* @return true if the user tried to move to a valid position.
*/
bool updateMaze(vector<string>& maze, char key)
{
    // Retrieve human's coordinates.

    int human_row, human_col;
    human_row =  findHuman(maze).first;
    human_col =  findHuman(maze).second;

    // Check to which direction the user
    // wants to move and store it.

    int dir_row, dir_col;

    switch(key)
    {
        case 'Q':
            dir_row = -1;
            dir_col = -1;
            break;
        case 'W':
            dir_row = -1;
            dir_col = 0;
            break;
        case 'E':
            dir_row = -1;
            dir_col = 1;
            break;
        case 'A':
            dir_row = 0;
            dir_col = -1;
            break;
        case 'S':
            dir_row = 0;
            dir_col = 0;
            break;
        case 'D':
            dir_row = 0;
            dir_col = 1;
            break;
        case 'Z':
            dir_row = 1;
            dir_col = -1;
            break;
        case 'X':
            dir_row = 1;
            dir_col = 0;
            break;
        case 'C':
            dir_row = 1;
            dir_col = 1;
            break;
            
        default:
            return false;
    }

    // Update the Human's coordinates
    // according to the direction.

    int new_human_row = human_row + dir_row;
    int new_human_col = human_col + dir_col;

    // Check whether the new position
    // results in the player's death.

    if(maze[new_human_row][new_human_col] != ' ' && maze[new_human_row][new_human_col] != 'H'){

        maze[new_human_row][new_human_col] = 'h';
        maze[human_row][human_col] = ' ';
        return false;
    }

    // Update the maze.

    maze[human_row][human_col] = ' ';
    maze[new_human_row][new_human_col] = 'H';

    return true;

}