#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

void writeHighScores(string fileName, const vector<pair<string, int>> highScoresVector)
{
    ofstream file(fileName);
    file << "Player         - Time\n----------------------\n";
    for(auto i = 0; i < highScoresVector.size(); i++)
    {
        file << highScoresVector[i].first << "- " << highScoresVector[i].second << endl;
    }
    file.close();
}

// Driver function to sort the vector elements
// by second element of pairs
bool sortBySec(const pair<string,int> &a, const pair<string,int> &b)
{
    return (a.second < b.second);
}

void addHighScore(vector<pair<string, int>>& highScoresVector, string name, int time)
{
    pair<string, int> highScore;
    highScore.first = name;
    highScore.second = time;
    highScoresVector.push_back(highScore);
    sort(highScoresVector.begin(), highScoresVector.end(), sortBySec);
}

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