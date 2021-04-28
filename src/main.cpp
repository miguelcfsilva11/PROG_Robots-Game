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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
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
            
            const int MAX_NAME_LENGTH = 15;

            // Get the user's name
            string playerName;
            bool validName = false;
            int nameLength;
            while(!validName)
            {
                cout << "Enter your name (up to 15 characters): ";
                getline(cin, playerName);
                int nonAsciiChars = 0;
                nameLength = 0;
                bool hyphenChar = false;

                for(int i = 0; playerName[i]; i++)
                {
                    if(int(playerName[i]) >= 0)
                        nameLength++;
                    else
                        nonAsciiChars++;
                    if(playerName[i] == '-')
                    {
                        hyphenChar = true;
                        break;
                    }
                }
                nameLength += nonAsciiChars / 2;
                if(nameLength > 15)
                {
                    cout << "Please enter a shorter name!" << endl;
                    continue;
                }
                if(hyphenChar)
                {
                    cout << "Please don't enter a name with a '-'" << endl;
                    continue;
                }
                validName = true;
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

            playerName += string(MAX_NAME_LENGTH - nameLength, ' ');

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
