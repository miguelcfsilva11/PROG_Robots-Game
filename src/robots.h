#ifndef ROBOTS_H
#define ROBOTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int robotsMovement (std::vector<std::string>& maze, std::vector<std::pair<int, int>>& robots);
void findRobots (std::vector<std::string>& maze, std::vector<std::pair<int, int>>& robots);

#endif