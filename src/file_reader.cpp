#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/******************************************************************************/

/**
 * This function iterates over a .txt file
 * and fills the given vector with its lines. 
*/

bool loadMaze(string fileName, vector<string>& maze)
{
    ifstream file(fileName);

    // Open the file and checks
    // whether it's a valid object.

    if (!file)
    {
        cerr << "Couldn't open the following file : " << fileName << endl;
        return false;
    }

    string row;
    int row_number = 0;

    while (getline(file, row))
    {
        if (row_number < 1){
            row_number++;
            continue;
        }
        
        maze.push_back(row);
        row_number++;
    }

    // Deallocate the resources needed to open
    // a file by closing it in the end of the
    // function.

    file.close();

    return true;
}