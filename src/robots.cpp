#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "game.h"
#include "robots.h"

using namespace std;


void robotsMovement (vector<string>& maze, vector<pair<int, int>>& robots)
{
    // Retrieve human's coordinates.

    int human_row, human_col = pair <int, int> findHuman (vector<string>& maze);

    for(int robot_id = 1; robot_id <= robots.size(); robot_id++){

            // For every located robot, compare its
            // position to the human's and find
            // the most efficient path that leads to him.

            robots[robots_id - 1][0] = robot_row;
            robots[robots_id - 1][1] = robot_col;

            if (maze[robot_row][robot_col] == "r")

                // In case our robot has been destroyed,
                // do not move it. It must remain stuck
                // until the end of the game.

                break;


            if (robot_row > human_row && robot_col > human_col) {
                if (maze[robot_row - 1][robot_col - 1] != " ")
                    maze[robot_row][robot_col] = "r";
                else{
                    maze[robot_row - 1][robot_col - 1] = "R";
                    maze[robot_row][robot_col] = " ";
                }
            }

            else if (robot_row < human_row && robot_col < human_col) {
                if (maze[robot_row + 1][robot_col + 1] != " ")
                    maze[robot_row][robot_col] = "r";
                else{
                    maze[robot_row + 1][robot_col + 1] = "R";
                    maze[robot_row][robot_col] = " ";
                }

            }

            else if (robot_row < human_row && robot_col > human_col) {
                if (maze[robot_row + 1][robot_col - 1] != " ")
                    maze[robot_row][robot_col] = "r";
                else{
                    maze[robot_row + 1][robot_col - 1] = "R";
                    maze[robot_row][robot_col] = " ";
                }

            }

            else if (robot_row > human_row && robot_col < human_col) {
                if (maze[robot_row - 1][robot_col + 1] != " ")
                    maze[robot_row][robot_col] = "r";
                else{
                    maze[robot_row - 1][robot_col + 1] = "R";
                    maze[robot_row][robot_col] = " ";
                }

            }

            else if (robot_row > human_row) {
                if (maze[robot_row - 1][robot_col] != " ")
                    maze[robot_row][robot_col] = "r";
                else{
                    maze[robot_row - 1][robot_col] = "R";
                    maze[robot_row][robot_col] = " ";
                }

            }
            
            else if (robot_row < human_row) {
                if (maze[robot_row + 1][robot_col] != " ")
                    maze[robot_row][robot_col] = "r";
                else{
                    maze[robot_row + 1][robot_col] = "R";
                    maze[robot_row][robot_col] = " ";
                }

            }

            else if (robot_col > human_col) {
                if (maze[robot_row][robot_col - 1] != " ")
                    maze[robot_row][robot_col] = "r";
                else{
                    maze[robot_row][robot_col - 1] = "R";
                    maze[robot_row][robot_col] = " ";
                }

            }

            else if (robot_col < human_col) {
                if (maze[robot_row][robot_col + 1] != " ")
                    maze[robot_row][robot_col] = "r";
                else{
                    maze[robot_row][robot_col + 1] = "R";
                    maze[robot_row][robot_col] = " ";
                }

            }
    }

    
}

void findRobots (vector<string>& maze, vector<pair<int, int>>& robots)

{
    for(int row = 0; row < maze.size(); row++){
        for(int col = 0; col < maze[row].size(); col++){
            if (maze[row][col] == 'R'){
                robots.push_back((row, col))

}