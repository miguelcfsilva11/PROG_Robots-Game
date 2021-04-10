#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

pair <int, int> findHuman (vector<string>& maze);
bool isAlive(std::vector<std::string>& maze);
bool updateVector(std::vector<std::string>& maze, char key);

#endif
