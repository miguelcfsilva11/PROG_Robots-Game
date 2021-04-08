#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "game.h"

using namespace std;

bool isAlive(vector<string>& maze)
{
    /**
    * Checks whether the player is alive by evaluating 
    * his surroundings. In case he's in contact with either
    * a robot or a fence, then we must declare him dead.
    * 
    * @return true if the human is safe.
    * @return false in case there's either a robot or a fence touching him.
    */


    int human_row, human_col; // Human's coordinates.

    for(int row = 0; row < maze.size(); row++){
        for(int col = 0; col < maze[row].size(); col++){
            if (maze[row][col] == 'H'){
                
                // If we find the human, store his
                // location in the following variables.

                human_row = row;
                human_col = col;
                break;

            }
        }
    }

    // To check if he's in danger, we must evaluate
    // the squares that are above, underneath and next to him.
    
    if (human_row != maze.size()-1)

        // We may only verify if there are enemies beneath him
        // in case he is not at the lowest row of the maze, in order words,
        // when the 'H' character is not on the last stored string.
        // This same logic applies to the conditionals that follow.

        if (maze[human_row + 1][human_col] == 'R' || maze[human_row + 1][human_col] == '*')
            return false;

    if (human_row != 0)
        if (maze[human_row - 1][human_col] == 'R' || maze[human_row - 1][human_col] == '*')
            return false;

    if (human_col != maze[human_row].size()-1)
        if (maze[human_row][human_col + 1] == 'R' || maze[human_row][human_col + 1] == '*')
            return false;

    if (human_col != 0)
        if (maze[human_row][human_col - 1] == 'R' || maze[human_row][human_col - 1] == '*')
            return false;

    return true;

}