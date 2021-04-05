
#include "file_reader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    char key;
	vector<string> maze;
	string fileName = "mazes\MAZE_01.TXT";
    
    cout << "Press a key to load Maze 1!";
    cin >> key;

	fillVector(fileName, maze);

}