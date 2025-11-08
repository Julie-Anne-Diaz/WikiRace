#pragma once

#include <map>
#include <fstream>
#include <vector>
#include <string>

std::string toLower(std::string s);

std::vector<std::string> BFS(std::string start, std::string end);
std::vector<std::string> DFS(std::string start, std::string end);


