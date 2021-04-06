#include <iostream>
#include <iomanip>
#include <ios>
#include <limits>
#include "menu.h"
#include <fstream>
#include <string>
#include <vector>
#include "file_reader.h"

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
	string fileName = "../mazes/MAZE_01.txt";

    cout << "Press a key to load Maze 1: ";
    cin >> key;

    fillVector(fileName, maze);

    return 0;
}
