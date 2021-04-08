#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void loadMaze(string fileName, vector<string>& maze)

    // This function iterates over a .txt file
    // and fills the given vector with its lines.

{
    ifstream file(fileName);

    // Open the file and checks
    // whether it's a valid object.

    if (!file)
    {
        cerr << "Couldn't open the following file : " << fileName << endl;
    }
    string row;
    while (getline(file, row))
    {
        maze.push_back(row);
    }

    // Deallocate the resources needed to open
    // a file by closing it in the end of the
    // function.

    file.close();
}