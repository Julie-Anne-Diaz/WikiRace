#pragma once

#include <map>
#include <fstream>
#include <vector>
#include <string>

class WikiGraph{
    std::map<std::string,std::vector<std::string>> adj;
public:
    WikiGraph();
    WikiGraph(std::string filepath);
    bool makeGraph(std::string filepath);
    std::vector<std::string> BFS(std::string start, std::string end);
    std::vector<std::string> DFS(std::string start, std::string end);
};


