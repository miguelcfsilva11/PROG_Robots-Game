#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


void readHighScores(std::string fileName, std::vector<std::pair<std::string, int>>& highScoresVector);
void createFile(std::string filename);

#endif
