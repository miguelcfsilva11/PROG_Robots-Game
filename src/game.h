#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool isAlive(std::vector<std::string>& maze);

bool updateVector(std::vector<std::string>& maze, char key);

#endif