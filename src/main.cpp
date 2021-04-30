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

    // Display the menu and keep displaying
    // it until the user chooses to exit the
    // program or play the game.

    int menuOption = menu();
    while (menuOption == 1)
        menuOption = menu();

    // End the program if the user chooses
    // to exit, else start the game

    if (menuOption == 0)
        return 0;

    char key;
    int maze_number;
    bool mazeLoaded = false;
    string fileName;

	vector <string> maze;
    vector <pair<int, int>> robots;

    cout << "Choose the number of the maze you wish to challenge: ";

   // Ask the user for the number of the
   // maze that they want to play until
   // they enter a valid number, and
   // load the maze to a vector.

    while(!mazeLoaded)
    {
        cin >> maze_number;
        
        // Checking for and dealing with invalid input.
        
        if(cin.fail())
        {
            if(cin.eof())
                 // Exit the program.

                return 0;
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Pick a valid number: ";
                continue;
            }
        }

        else 
        {
            if(cin.peek() != '\n')
            {
                cout << "Pick a valid number: ";
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }

        if (maze_number >= 10)
            fileName = "MAZE_" + to_string(maze_number) + ".TXT";
        else
            fileName = "MAZE_0" + to_string(maze_number) + ".TXT";
    
        if (!loadMaze(fileName, maze)){

            cout << "Choose a valid maze number: ";
            continue;
        }

        mazeLoaded = true;
    }

    cout << "Press enter to start Maze " << maze_number << ": ";
    getchar();

    findRobots(maze, robots);

    // Start counting the time that the
    // user takes to win the game.
    time_t startTime = time(0);

    // Main game loop: while the user
    // is alive keep asking for input
    // representing the direction
    // that the user wants to move.

    while (isAlive(maze)){

        // Display the maze

        cout << "      THE MAZE    " << endl;
        for (auto i = 0; i < maze.size(); i++)
            cout << maze[i] << endl;
        
        // Ask for a direction

        cout << "\nPick a direction: ";
        char direction;
        cin >> direction;

        // Checking for and dealing with invalid input.

        if(cin.fail())
        {
            if(cin.eof())

                // Exit the program.
                
                return 0;

            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid move! Please pick a different direction." << endl;
                continue;
            }
        }
        else 
        {
            if(cin.peek() != '\n')
            {
                cout << "Pick a valid direction!";
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }

        // Move in the chosen direction and
        // check if the user moved to a position
        // where he would die.

        if(!updateMaze(maze, toupper(direction)))
        {
            continue;
        }

        // Move the robots accordingly.

        robotsMovement(maze, robots);
        findRobots(maze, robots);
        
        // Check if the user has won the game
        // (killed all the robots and is still alive),
        // display the final state of the maze,
        // and add a new highscores entry.

        if (robots.size() == 0 && isAlive(maze)){
            cout << "      THE MAZE    " << endl;
            for (auto i = 0; i < maze.size(); i++)
                cout << maze[i] << endl;
            cout << "       You won!         " << endl;
            cout << "You killed all the robots!" << endl;

            // Take note of the time it took
            // the user to win the game.

            int secondsToWin = difftime(time(0), startTime);
            
            const int MAX_NAME_LENGTH = 15;

            // Keep asking the user to enter his
            // name until he chooses a valid one.

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

                // Count the length of the given name,
                // taking into account the possibility
                // of existing non-ascii characters.

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

                // Check if the given name is whithin
                // the allowed name length and if it does
                // not contain any ' - '. We don't allow
                // the use of this character because it
                // would interfere with the reading of
                // the high scores file.

                if(nameLength > MAX_NAME_LENGTH)
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

            string highScoresFilename = fileName.substr(0,7) + "_WINNERS.TXT";

            // Check if the file exists and
            // create it if it doesn't.
            
            ifstream highScoresFile;
            highScoresFile.open(highScoresFilename);
            if(highScoresFile)
                highScoresFile.close();
            else
                createFile(highScoresFilename);

            // If necessary, add spaces in front
            // of the name in order to make it
            // always have the same length.

            playerName += string(MAX_NAME_LENGTH - nameLength, ' ');

            // Read the already existing high scores,
            // add the new entry, sort them, and write
            // the updated scoreboard to the file.

            vector<pair<string, int>> highScoresVector;
            readHighScores(highScoresFilename, highScoresVector);
            addHighScore(highScoresVector, playerName, secondsToWin);
            writeHighScores(highScoresFilename, highScoresVector);

            return 0;
        }
    }

    // If we break out of the game loop,
    // it means the user is no longer
    // alive, which means he lost the game,
    // so we display the final state of the maze.

    cout << "      THE MAZE    " << endl;
    for (auto i = 0; i < maze.size(); i++)
        cout << maze[i] << endl;
    cout << "       You lost!         " << endl;
    cout << "Your player is dead meat!" << endl;

    return 0;
    
}
