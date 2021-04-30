// T05_G02

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::pair <int, int> findHuman (std::vector<std::string>& maze);
bool isAlive(std::vector<std::string>& maze);
bool updateMaze(std::vector<std::string>& maze, char key);

#endif
