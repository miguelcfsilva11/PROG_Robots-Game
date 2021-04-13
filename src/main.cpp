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

using namespace std;

int main()
{
    int menuOption = menu();
    while(menuOption == 1)
        menuOption = menu();

    if(menuOption == 0)
        return 0;

    char key;
	vector<string> maze;
    vector <pair<int, int>> robots;
	string fileName = "MAZE_01.TXT";
    cout << "Press a key to load Maze 1: ";
    cin >> key;

   loadMaze(fileName, maze);
    
    if (isAlive(maze))
        cout << "Your player is alive and safe!" << endl;
    else
        cout << "Your player is dead meat." << endl;

    vector<pair<string, int>> aaa;
    readHighScores("MAZE_01_WINNERS.TXT", aaa);
    for (auto i = aaa.begin(); i != aaa.end(); ++i)
        cout << (*i).first << "- " << (*i).second << endl;

    return 0;
}
