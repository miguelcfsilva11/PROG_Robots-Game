#include <iostream>
#include <iomanip>
#include <ios>
#include <limits>
#include <fstream>
#include <string>
#include <vector>

#include "menu.h"
#include "file_reader.h"
#include "game.h"
#include "high_score.h"
#include "robots.h"

using namespace std;

int main()
{
    int menuOption = menu();
    while (menuOption == 1)
        menuOption = menu();

    if (menuOption == 0)
        return 0;

    char key;

	vector <string> maze;
    vector <pair<int, int>> robots;

	string fileName = "MAZE_01.TXT";
    cout << "Press a key to load Maze 1: ";
    cin >> key;

    loadMaze(fileName, maze);
    findRobots(maze, robots);

    while (isAlive(maze)){

        cout << "      THE MAZE    " << endl;
        for (auto i = 0; i < maze.size(); i++)
            cout << maze[i] << endl;
        
        cout << "\nPick an direction: ";
        cin >> key;
        
        if(!updateMaze(maze, toupper(key)))
        {
            cout << "Invalid move! Please pick a different direction." << endl;
            continue;
        }
        robotsMovement(maze, robots);

        if (findHuman(maze) == make_pair(-1,-1))
            break;

        findRobots(maze, robots);
        
        if (robots.size() == 0){
            cout << "      THE MAZE    " << endl;
            for (auto i = 0; i < maze.size(); i++)
                cout << maze[i] << endl;
            cout << "       You won!         " << endl;
            cout << "You killed all the robots!" << endl;
            return 0;
        }
    }

    cout << "      THE MAZE    " << endl;
    for (auto i = 0; i < maze.size(); i++)
        cout << maze[i] << endl;
    cout << "       You lost!         " << endl;
    cout << "Your player is dead meat!" << endl;

    return 0;
    
}
