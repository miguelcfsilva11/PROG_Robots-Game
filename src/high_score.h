#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

void writeHighScores(std::string fileName, const std::vector<std::pair<std::string, int>> highScoresVector);
void addHighScore(std::vector<std::pair<std::string, int>>& highScoresVector, std::string name, int time);
void readHighScores(std::string fileName, std::vector<std::pair<std::string, int>>& highScoresVector);
void createFile(std::string filename);

#endif
