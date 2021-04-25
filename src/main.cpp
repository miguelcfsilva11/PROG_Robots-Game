#include <iostream>
#include <iomanip>
#include <ios>
#include <limits>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

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

    time_t startTime = time(0);

    while (isAlive(maze)){

        cout << "      THE MAZE    " << endl;
        for (auto i = 0; i < maze.size(); i++)
            cout << maze[i] << endl;
        
        cout << "\nPick a direction: ";
        cin >> key;
        
        if(!updateMaze(maze, toupper(key)))
        {
            cout << "Invalid move! Please pick a different direction." << endl;
            continue;
        }
        robotsMovement(maze, robots);
        findRobots(maze, robots);
        
        if (robots.size() == 0){
            cout << "      THE MAZE    " << endl;
            for (auto i = 0; i < maze.size(); i++)
                cout << maze[i] << endl;
            cout << "       You won!         " << endl;
            cout << "You killed all the robots!" << endl;

            int secondsToWin = difftime(time(0), startTime);
            
            const int MAX_NAME_LENGTH = 3;

            // Get user name
            string playerName;
            bool lengthLimit = false;
            while(!lengthLimit)
            {
                cout << "Enter your name (up to 15 characters): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, playerName);
                if(playerName.length() > MAX_NAME_LENGTH)
                    cout << "Please enter a shorter name!" << endl;
                else
                    lengthLimit = true;
            }

            string highScoresFilename = "MAZE_01_WINNERS.TXT";

            // Check if the file exists and
            // create it if it doesn't
            ifstream highScoresFile;
            highScoresFile.open(highScoresFilename);
            if(highScoresFile)
                highScoresFile.close();
            else
                createFile(highScoresFilename);

            playerName += string(MAX_NAME_LENGTH - playerName.length(), ' ');

            vector<pair<string, int>> highScoresVector;
            readHighScores(highScoresFilename, highScoresVector);
            addHighScore(highScoresVector, playerName, secondsToWin);
            writeHighScores(highScoresFilename, highScoresVector);

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
