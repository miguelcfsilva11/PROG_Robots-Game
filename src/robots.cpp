#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "game.h"
#include "robots.h"

using namespace std;



/**
* Updates robots' places in the maze, one by one.
* 
* @return 0 if every robot has moved atleast once or when the human has been captured.
*/

int robotsMovement (vector<string>& maze, vector<pair<int, int>>& robots)
{
    // Retrieve human's coordinates.
        
    int human_row, human_col;
    human_row =  findHuman(maze).first;
    human_col =  findHuman(maze).second;

    for(int robot_id = 1; robot_id <= robots.size(); robot_id++){

        int robot_row, robot_col;

        // For every located robot, compare its
        // position to the human's and find
        // the most efficient path that leads to him.

        robot_row = robots[robot_id - 1].first;
        robot_col = robots[robot_id - 1].second;

        if (maze[robot_row][robot_col] == 'r')

            // In case our robot has been destroyed,
            // do not move it. It must remain stuck
            // until the end of the game.

            break;


        // When updating their places, we need to make sure
        // that they follow the shortest path possible to the human.
        // To do so, we first need to check if moving in a diagonal
        // would benefit the robot, as it covers more space.


        if (robot_row > human_row && robot_col > human_col) {
            if (maze[robot_row - 1][robot_col - 1] == 'r')
                maze[robot_row][robot_col] = ' ';

            else if (maze[robot_row - 1][robot_col - 1] == '*'){
                maze[robot_row - 1][robot_col - 1] = 'r';
                maze[robot_row][robot_col] = ' ';
            }
            else if (maze[robot_row - 1][robot_col - 1] == 'H'){
                maze[robot_row - 1][robot_col - 1] = 'h';
                maze[robot_row][robot_col] = ' ';

                // When capturing the human, there is no need for the
                // remaining robots to move. The player has been killed.
                // Stop their movement.

                return 0;
            }

            else{
                maze[robot_row - 1][robot_col - 1] = 'R';
                maze[robot_row][robot_col] = ' ';

                // Updating their position on 'robots' vector.

                robots[robot_id - 1].first--;
                robots[robot_id - 1].second--;

                }
            }

        else if (robot_row < human_row && robot_col < human_col) {
            if (maze[robot_row + 1][robot_col + 1] == 'r')
                maze[robot_row][robot_col] = ' ';

            else if (maze[robot_row + 1][robot_col + 1] == '*'){
                maze[robot_row + 1][robot_col + 1] = 'r';
                maze[robot_row][robot_col] = ' ';
            }

            else if (maze[robot_row + 1][robot_col + 1] == 'H'){
                maze[robot_row + 1][robot_col + 1] = 'h';
                maze[robot_row][robot_col] = ' ';

                return 0;
            }

            else{
                maze[robot_row + 1][robot_col + 1] = 'R';
                maze[robot_row][robot_col] = ' ';

                robots[robot_id - 1].first++;
                robots[robot_id - 1].second++;

            }

        }

        else if (robot_row < human_row && robot_col > human_col) {
            if (maze[robot_row + 1][robot_col - 1] == 'r')
                maze[robot_row][robot_col] = ' ';

            else if (maze[robot_row + 1][robot_col - 1] == '*'){
                maze[robot_row + 1][robot_col - 1] = 'r';
                maze[robot_row][robot_col] = ' ';
            }
            
            else if (maze[robot_row + 1][robot_col - 1] == 'H'){
                maze[robot_row + 1][robot_col - 1] = 'h';
                maze[robot_row][robot_col] = ' ';

                return 0;
            }

            else{
                maze[robot_row + 1][robot_col - 1] = 'R';
                maze[robot_row][robot_col] = ' ';

                robots[robot_id - 1].first++;
                robots[robot_id - 1].second--;

            }

        }

        else if (robot_row > human_row && robot_col < human_col) {
            if (maze[robot_row - 1][robot_col + 1] == 'r')
                maze[robot_row][robot_col] = ' ';
            
            else if (maze[robot_row - 1][robot_col + 1] == '*'){
                maze[robot_row - 1][robot_col + 1] = 'r';
                maze[robot_row][robot_col] = ' ';
            }

            else if (maze[robot_row - 1][robot_col + 1] == 'H'){
                maze[robot_row - 1][robot_col + 1] = 'h';
                maze[robot_row][robot_col] = ' ';

                return 0;
            }

            else{
                maze[robot_row - 1][robot_col + 1] = 'R';
                maze[robot_row][robot_col] = ' ';

                robots[robot_id - 1].first--;
                robots[robot_id - 1].second++;

            }

        }

        // If the diagonals are not optimal, the robot
        // must trace a straight line to the user's position.

        else if (robot_row > human_row) {
            if (maze[robot_row - 1][robot_col] == 'r')
                maze[robot_row][robot_col] = ' ';
            
            else if (maze[robot_row - 1][robot_col] == '*'){
                maze[robot_row - 1][robot_col] = 'r';
                maze[robot_row][robot_col] = ' ';
            }
            
            else if (maze[robot_row - 1][robot_col] == 'H'){
                maze[robot_row - 1][robot_col] = 'h';
                maze[robot_row][robot_col] = ' ';
                
                return 0;
            }

            else{
                maze[robot_row - 1][robot_col] = 'R';
                maze[robot_row][robot_col] = ' ';

                robots[robot_id - 1].first--;

            }

        }
        
        else if (robot_row < human_row) {
            if (maze[robot_row + 1][robot_col] == 'r')
                maze[robot_row][robot_col] = ' ';

            else if (maze[robot_row + 1][robot_col] == '*'){
                maze[robot_row + 1][robot_col] = 'r';
                maze[robot_row][robot_col] = ' ';
            }

            else if (maze[robot_row + 1][robot_col] == 'H'){
                maze[robot_row + 1][robot_col] = 'h';
                maze[robot_row][robot_col] = ' ';

                return 0;
            }

            else{
                maze[robot_row + 1][robot_col] = 'R';
                maze[robot_row][robot_col] = ' ';

                robots[robot_id - 1].first++;

            }

        }

        else if (robot_col > human_col) {
            if (maze[robot_row][robot_col - 1] == 'r')
                maze[robot_row][robot_col] = ' ';
            
            else if (maze[robot_row][robot_col - 1] == '*'){
                maze[robot_row][robot_col - 1] = 'r';
                maze[robot_row][robot_col] = ' ';
            }

            else if (maze[robot_row][robot_col - 1] == 'H'){
                maze[robot_row][robot_col - 1] = 'h';
                maze[robot_row][robot_col] = ' ';

                return 0;
            }

            else{
                maze[robot_row][robot_col - 1] = 'R';
                maze[robot_row][robot_col] = ' ';

                robots[robot_id - 1].second--;

            }

        }

        else if (robot_col < human_col) {
            if (maze[robot_row][robot_col + 1] == 'r')
                maze[robot_row][robot_col] = ' ';
            
            else if (maze[robot_row][robot_col + 1] == '*'){
                maze[robot_row][robot_col + 1] = 'r';
                maze[robot_row][robot_col] = ' ';
            }
            
            else if (maze[robot_row][robot_col + 1] == 'H'){
                maze[robot_row][robot_col + 1] = 'h';
                maze[robot_row][robot_col] = ' ';

                return 0;
            }

            else{
                maze[robot_row][robot_col + 1] = 'R';
                maze[robot_row][robot_col] = ' ';

                robots[robot_id - 1].second++;

            }

        }
    }

    return 0;
    
}

/**
* Searches for robots in the maze
* stores their coordinates in a
* vector of pairs.
*
* @return
*/

void findRobots (vector<string>& maze, vector<pair<int, int>>& robots)

{
    robots.clear();

    for(int row = 0; row < maze.size(); row++){
        for(int col = 0; col < maze[row].size(); col++){
            if (maze[row][col] == 'R'){

                // The robots' IDs will be the value of their
                // respective index when stored in this vector
                // this vector incremented by one.

                robots.push_back(make_pair(row, col));
            }
        }
    }

}