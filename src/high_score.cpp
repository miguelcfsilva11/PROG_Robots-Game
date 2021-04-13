#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/**
* Reads the high scores from a given file and stores a pair of
* all the users and their high scores in a vector.
*
* @param fileName The name of the file to read from.
* @param highScores A vector where the high score pairs will be stored.
*/
void readHighScores(string fileName, vector<pair<string, int>>& highScoresVector)
{
    ifstream highScoresFile(fileName);
    string line;
    int i = 0;
    pair<string, int> highScore;
    while(getline(highScoresFile, line))
    {
        if(i < 2)
        {
            i++;
            continue;
        }

        highScore.first = line.substr(0, 15);
        highScore.second = stoi(line.substr(17));
        highScoresVector.push_back(highScore);

        i++;

    }
}

/**
* Creates a file with a basic template for storing the high scores.
*
* @param fileName The name of the file to be created.
*/
void createFile(string fileName)
{
    ofstream file(fileName);
    file << "Player         - Time\n----------------------\n";
    file.close();
}