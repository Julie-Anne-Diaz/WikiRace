#pragma once

#include <vector>
#include <string>

#include "binManagement.hpp"

std::vector<std::string> BFS(const std::vector<BinEntry>& bins, const std::string& start, const std::string& end);
std::vector<std::string> DFS(const std::vector<BinEntry>& bins, const std::string& start, const std::string& end);


